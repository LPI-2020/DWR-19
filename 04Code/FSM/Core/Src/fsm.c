/*
 * fsm.c
 *
 * FSM module
 *
 *  Created on: June 3, 2021
 *
 */
#include "fsm.h"

#include "motion.h"
#include "timeout.h"
#include "bluetooth.h"
#include "debounce.h"

#include "lfollower.h"	// using lfollower_rotate
#include "rfid-rc522.h"	// using read_RFID

#include "tests.h"

#include <stdlib.h>
#include "usart.h"

// -------- removbe this
#include "stop_sensors.h"

/******************************************************************************
Private Defines
******************************************************************************/
// User button debounce
debounce_t button;

/******************************************************************************
Route Defines
******************************************************************************/
checkpoint_t route1[5] = {
		{
			.RFID = "0xc3ed9705",
			.action = ACT_FORWARD
		},
		{
			.RFID = "0xa31cd604",
			.action = ACT_STOP
		},
		{
			.RFID = "0x034bfc03",
			.action = ACT_LEFT
		},
		{
			.RFID = "0x53fde405",
			.action = ACT_STOP
		},
		// end of Checkpoint Array
		{
			.RFID = 0,
			.action = 0
		}
};
/******************************************************************************
FSM state functions
******************************************************************************/
static void s_stopped(void);
static void s_receive(void);

static void s_flw_line(void);
static void s_rd_rfid(void);
static void s_next_mov(void);
static void s_rotate(void);

static void s_error(void);

/******************************************************************************
FSM current state pointer
******************************************************************************/
void (*fsm_func_ptr[])(void) = {
		s_stopped,
		s_receive,

		s_flw_line,
		s_rd_rfid,
		s_next_mov,
		s_rotate,

		s_error
};

/******************************************************************************
FSM flags
******************************************************************************/
// Current FSM state
uint8_t state = 0;
// Next FSM state
uint8_t nstate = 0;

// Route pointer to the selected route
checkpoint_t *route_ptr = NULL;
// first rfid
static checkpoint_t *route_base_ptr = NULL;

// Direction of the next movement at junction
static uint8_t next_move_dir = 0;

// returning:
//		+1 - going forward
// 		-1 - comming back
static int returning = 1;

/******************************************************************************
State Stopped
******************************************************************************/
const static uint8_t returning_nstate_arr[] =
{
		S_ROTATE,
		S_FLW_LINE
};

static void s_stopped(void)
{
	uint8_t returning_nstate = returning;

//	write_led(LRED,0);
//	write_led(LBLUE,0);
//	write_led(LGREEN,0);

	// stop movement
	motion_stop();

	// returning_nstate is -1 or +1
	returning_nstate += 1;
	returning_nstate >>= 1;
	// returning_nstate is 0 or +1

	// is there a route available?
	if(route_ptr == NULL)
	{
		bluet_receive();

		if(bluet_status == BLUET_RECEIVING)
			// receiving new route
			nstate = S_RECEIVE;
	}

	else if(motion_status == MOT_OK)
	{
		// obstacle is not there anymore and timer not finished
		// restart movement
		nstate = S_FLW_LINE;
		UART_puts(&bluet_uart,"Restart movement\n\r");
	}

	else if(motion_status == MOT_TIMEOUT)
	{
		// obstacle has been there for too long
		// continue to error state
		nstate = S_ERROR;
		UART_puts(&bluet_uart,"Obstacle timeout\n\r");
	}

	else if(button.pin_output == 1)// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> adicionar condiçº~ies
	{
		pick_num_sec = 0;
		pick_timeout_ctrl = 0;

		nstate = returning_nstate_arr[returning_nstate];
	}

	else if((motion_status == MOT_OFF) && (pick_up_timeout))
	{
		// Restart movement.
		pick_up_timeout = 0;
		UART_puts(&bluet_uart,"Pick up timeout\n\r");

		nstate = returning_nstate_arr[returning_nstate];
	}

	// Else, continue in S_STOPPED
}

/******************************************************************************
State Receive
******************************************************************************/
static void s_receive(void)
{
//	write_led(LRED,0);
//	write_led(LBLUE,0);
//	write_led(LGREEN,1);

	// receives and parses commands by uart
	// if received with success returns 0 (bluet_ok)
	bluet_receive();

	if(bluet_status == BLUET_OK)
	{
		// save route base pointer
		route_base_ptr = route_ptr;

		// going forward
		returning = +1;

		// route received
		// bluetooth ready to receive again
		bluet_status = BLUET_READY;

		// initialize debounce button
		debounce_start(&button, USER_BTN_PORT, USER_BTN_PIN);

		// Wait for user_button
		nstate = S_STOPPED;
	}

	// Else nstate = S_RECEIVE
}

/******************************************************************************
State Follow Line
******************************************************************************/
static void s_flw_line(void)
{
//	write_led(LRED,0);
//	write_led(LBLUE,1);
//	write_led(LGREEN,0);

	// start movement
	motion_start();

	switch((uint8_t)motion_status)
	{
		case MOT_CROSS_FOUND:
			// Cross Found
			UART_puts(&bluet_uart,"Cross Found\n\r");
			nstate = S_RD_RFID;
			break;

		case MOT_HOLD:
			// Obstacle found
			UART_puts(&bluet_uart,"Obstacle Found\n\r");
			nstate = S_STOPPED;
			break;

		case MOT_ERR:
			// Out of route
			UART_puts(&bluet_uart,"Out of route\n\r");
			nstate = S_ERROR;
	}

	// Else, continue following line
}

/******************************************************************************
State Read RFID
******************************************************************************/
// RFID struct
static rfid_t rfid = {
		.CardID = {0},
		.CardID_str = 0,
		.type = 0
};

static void s_rd_rfid(void)
{
	uint8_t err;

//	write_led(LRED,0);
//	write_led(LBLUE,1);
//	write_led(LGREEN,1);

	// start movement
	// wait for RFID read or timeout (POLLING MODE)
	err = RFID_read(&rfid, RFID_TIMEOUT);

	// read RFID correctly?
	if(err == MI_OK)
	{
		// converts CardID to an hexadecimal string
		bin_to_strhex((unsigned char *)rfid.CardID, sizeof(rfid.CardID), &rfid.CardID_str);

		// calculate next movement on the route
		nstate = S_NEXT_MOV;
	}
	else
	{
		// RFID timeout
		// continue to error state
		UART_puts(&bluet_uart, "RFID timeout\n\r");

		// stop movement at S_ERROR
		nstate = S_ERROR;
	}
}

/******************************************************************************
State Next Movement
******************************************************************************/
uint8_t turn_func(void)
{
	// dir = 0 -> move right
	// dir = 1 -> move left
	char dir = route_ptr->action;

	dir <<= 1;
	dir -= 1;

	next_move_dir = dir * returning;

	char str[32];
	snprintf(str, sizeof(str), "Change to dir[%d].\n\r", next_move_dir);
	UART_puts(&bluet_uart, str);

	return S_ROTATE;
}

uint8_t forward_func(void)
{
	UART_puts(&bluet_uart,"Continue moving.\n\r");
	return S_FLW_LINE;
}

uint8_t stop_func(void)
{
	// coming back -> follow line and dont stop
	if(returning == -1)
		return S_FLW_LINE;

	// else, room found
	// start pick up timeout
	UART_puts(&bluet_uart,"Room Found.\n\r");

	motion_status = MOT_OFF;
	// stop movement
	motion_stop();

	pick_timeout_ctrl = 1;

	return S_STOPPED;
}

uint8_t (*next_move_func [])(void) = {
	turn_func,
	turn_func,
	forward_func,
	stop_func
};

static void s_next_mov(void)
{
//	write_led(LRED,1);
//	write_led(LBLUE,0);
//	write_led(LGREEN,0);

	// route can be used?
	if((route_ptr == NULL) || (route_base_ptr == NULL))
	{
		UART_puts(&bluet_uart,"Route not defined.\n\r");

		// avoid bad memory access
		nstate = S_ERROR;
		return;
	}

	// move to the next checkpoint in route
	route_ptr += returning;

	if(strcmp(route_ptr->RFID, rfid.CardID_str) == 0)
		// rfid is as expected
		// execute next move
		nstate = next_move_func[route_ptr->action]();

	// robot at route start point?
	else if(route_ptr == route_base_ptr)
	{
		// returned to starting point
		// signal route finished from route_ptr
		route_ptr = NULL;
		nstate = S_STOPPED;
	}
	else
	{
		// detected RFID but there is no match with route
		UART_puts(&bluet_uart,"RFID not as expected\n\r");
		nstate = S_ERROR;
	}

	if(((route_ptr + 1)->RFID == 0) && (route_ptr != route_base_ptr))
	{
		// last rfid in the route diferent from the firt rfid
		// turns around
		next_move_dir = MOVE_LEFT;
		// sinalises that the robot is returning to the start point
		returning = -1;
	}
}

/******************************************************************************
State Rotate
******************************************************************************/
static void s_rotate(void)
{
	uint8_t err;

//	write_led(LRED,1);
//	write_led(LBLUE,0);
//	write_led(LGREEN,1);

	motion_stop();

	// rotate to direction 'next_move_dir' (POLLING MODE)
	err = lfollower_rotate(next_move_dir, ROTATE_TIMEOUT);

	// rotate has returned error?
	if(err)
	{
		// rotate TIMEOUT
		// rotate was not successfull
		UART_puts(&bluet_uart, "Rotate timeout\n\r");
		nstate = S_ERROR;
	}
	else
		// turn completed. Restart following line
		nstate = S_FLW_LINE;
}

/******************************************************************************
State Error
******************************************************************************/
static void s_error(void)
{
//	write_led(LRED,1);
//	write_led(LBLUE,1);
//	write_led(LGREEN,0);

	// stop movement
	motion_stop();

	// send error messages
	if((route_ptr != NULL) && ((route_ptr - 1) >= route_base_ptr))
	{
		char str[32];
		UART_puts(&bluet_uart, "ERROR: last known location:\n\r");

		snprintf(str, sizeof(str), "RFID '%s'\n\r", (route_ptr - 1)->RFID);
		UART_puts(&bluet_uart, str);
	} else
		UART_puts(&bluet_uart, "ERROR: ....\n\r");

	while(1)
		;
}

