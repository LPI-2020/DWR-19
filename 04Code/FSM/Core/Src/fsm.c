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
ST_debounce button;

/******************************************************************************
Route Defines
******************************************************************************/
checkpoint_t route1[4] = {
		{
			.RFID = "0x034BFC0",
			.action = ACT_FORWARD
		},
		{
//			.RFID = "0x034BFC0",
			.RFID = "0xa31cd604",
			.action = ACT_STOP
		},
		{
			.RFID = "0xA31CD60" ,
			.action = ACT_LEFT
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

// Route finished flag
//uint8_t route_finished = 1;

// Route pointer to the selected route
checkpoint_t *route_ptr = NULL;
// first rfid
checkpoint_t *route_base_ptr = NULL;

// Direction of the next movement at junction
uint8_t next_move_dir = 0;
// returning:
//		+1 - going forward
// 		-1 - comming back
uint8_t returning = 1;

/******************************************************************************
State Stopped
******************************************************************************/
static void s_stopped(void)
{
//	write_led(LRED,0);
//	write_led(LBLUE,0);
//	write_led(LGREEN,0);

	// stop movement
	motion_stop();

	// is there a route available?
	//if(route_finished)
	if(route_ptr == NULL)
	{
		bluet_receive();

		if(bluet_status == BLUET_RECEIVING)
			// receiving new route
			nstate = S_RECEIVE;
	}

	//else if((!obs_found_flag) && (!obs_found_timeout))
	else if(motion_status == MOT_ON)
		// obstacle is not there anymore and timer not finished
		// restart movement
		nstate = S_FLW_LINE;

	//else if(obs_found_timeout)
	else if(motion_status == MOT_TIMEOUT)
		// obstacle has been there for too long
		// continue to error state
		nstate = S_ERROR;

//	else if((!route_finished) && ((button.pin_output == 1) || pick_up_timeout))
//	else if((button.pin_output == 1) || ((motion_status == MOT_OFF) && (timeout_flag)))
	else if((button.pin_output == 1) || ((motion_status == MOT_OFF) && (pick_up_timeout)))
	{
		//timeout_flag = 0;
		pick_up_timeout = 0;
		// Route not finished (have received a new route and User button pressed
		// or robot has been waiting too much time for user to pick up his goods.
		// Restart movement.
		nstate = S_FLW_LINE;
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
//		route_ptr = route1;// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> remove this


		// save route base pointer
		route_base_ptr = route_ptr;

		// route received
		//route_finished = 0;
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
			// obstacle found
			UART_puts(&bluet_uart,"Obstacle Found\n\r");
			nstate = S_STOPPED;
			break;

		case MOT_ERR:
			UART_puts(&bluet_uart,"Out of route\n\r");
			// out of route
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

//	char str[32];
//	snprintf(str, sizeof(str), "LF[%d]ST[%d]\n\r", lfollower_status, stop_detector_status);
//	UART_puts(&bluet_uart, str);

	// start movement
	// wait for RFID read or timeout (POLLING MODE)
	err = RFID_read(&rfid, RFID_TIMEOUT);

//	// stop movement
//	motion_stop();
//	// signal motion off
//	motion_status = MOT_OFF;

//	UART_puts(&bluet_uart, "MotOFF.\n\r");

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

		// stop movement
		motion_stop();
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

//	timeout_start(PICK_UP_TIMEOUT);
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

	// is this the last RFID in the route?
	if((route_ptr + 1)->RFID == 0)
	{
		// check if this is the route start checkpoint
		if(route_ptr != route_base_ptr)
		{
			// last rfid in the route diferent from the firt rfid
			// turns around
			next_move_dir = MOVE_LEFT;
			// sinalises that the robot is returning to the start point
			returning = -1;

			UART_puts(&bluet_uart,"Return to origin\n\r");

			nstate = S_ROTATE;
		}
	}
	// robot at route start point?
	else if(route_ptr == route_base_ptr)
	{
		// returned to starting point
		// signal route finished from route_ptr
		route_ptr = NULL;
		//route_finished = 1;
		nstate = S_STOPPED;
	}

	else if(strcmp(route_ptr->RFID, rfid.CardID_str) == 0)
		// rfid is as expected
		// execute next move
		nstate = next_move_func[route_ptr->action]();

	else
	{
		// detected RFID but there is no match with route
		UART_puts(&bluet_uart,"RFID not as expected\n\r");
		nstate = S_ERROR;
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



	// send error messages
	// ...

//	if(error_timeout)
//	{
//		// shutdown robot
//		// ????
//	}
}

