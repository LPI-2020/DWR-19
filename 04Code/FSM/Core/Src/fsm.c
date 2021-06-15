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

#include "lfollower.h"	// using lfollower_rotate
#include "rfid-rc522.h"	// using read_RFID

#include "debounce.h"
#include "tests.h"

/******************************************************************************
Private Defines
******************************************************************************/
// User button debounce
ST_debounce button;

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
uint8_t route_finished = 1;

// New route incoming flag
//uint8_t new_route_incoming = 0;

// Timeout flags
//uint8_t pick_up_timeout = 0;
//uint8_t obs_found_timeout = 0;
//uint8_t rotate_timeout = 0;
//uint8_t read_rfid_timeout = 0;

// Direction of the next movement at junction
uint8_t next_move_dir = 0;

/******************************************************************************
State Stopped
******************************************************************************/
static void s_stopped(void)
{
	write_led(LRED,0);
	write_led(LBLUE,0);
	write_led(LGREEN,0);

	// stop movement
	motion_stop();

	if(route_finished)
	{
		bluet_receive();
		if(bluet_status == BLUET_RECEIVING)
			// route finished and receiving new route
			nstate = S_RECEIVE;

		// Else nstate = S_STOPPED
	}

	//else if((!obs_found_flag) && (!obs_found_timeout))
	else if((motion_status != MOT_HOLD) && (motion_status != MOT_TIMEOUT))
		// obstacle is not there anymore and timer not finished
		// restart movement
		nstate = S_FLW_LINE;

	//else if(obs_found_timeout)
	else if(motion_status == MOT_HOLD)
		// obstacle has been there for too long
		// continue to error state
		nstate = S_ERROR;

//	else if((!route_finished) && ((button.pin_output == 1) || pick_up_timeout))
	else if((!route_finished) && ((button.pin_output == 1) || (motion_status == MOT_OFF && timeout_flag)))
		// Route not finished (have received a new route and User button pressed
		// or robot has been waiting too much time for user to pick up his goods.
		// Restart movement.
		nstate = S_FLW_LINE;

	// Else, continue in S_STOPPED
}

/******************************************************************************
State Receive
******************************************************************************/
static void s_receive(void)
{
	write_led(LRED,0);
	write_led(LBLUE,0);
	write_led(LGREEN,1);


	bluet_receive();

	if(bluet_status == BLUET_OK)
	{
		// route received
		route_finished = 0;
		bluet_status = BLUET_READY;

		// initialize debounce button and start timer it used in S_STOPPED
		debounce_start(&button, USER_BTN_PORT, USER_BTN_PIN);

		nstate = S_STOPPED;
	}

	// Else nstate = S_RECEIVE

//	if(bluet_st == BLUET_OK)
//		// new route has been fully received
//		nstate = S_STOPPED;
//	else
//	{
//		err = bluet_receive();
//
//		if(err == BLUET_OK)
//		{
//			// route received
//			route_finished = 0;
//			bluet_st = BLUET_READY;
//			nstate = S_STOPPED;
//		}
//	}
}

/******************************************************************************
State Follow Line
******************************************************************************/
static void s_flw_line(void)
{
	write_led(LRED,0);
	write_led(LBLUE,1);
	write_led(LGREEN,0);
	// start movement
	motion_start();

	switch((uint8_t)motion_status)
	{
		case MOT_CROSS_FOUND:
			// Cross Found
			nstate = S_RD_RFID;
			break;
//		case MOT_ROOM_FOUND:
//			// Room Found
//			nstate = S_NEXT_MOV;
//			break;
		case MOT_HOLD:
			// obstacle found
			nstate = S_STOPPED;
			break;
		case MOT_ERR:
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
		.result = 0,
		.type = 0
};

static void s_rd_rfid(void)
{
	uint8_t err;

	write_led(LRED,0);
	write_led(LBLUE,1);
	write_led(LGREEN,1);

	// start movement
	// wait for RFID read or timeout (POLLING MODE)
	err = RFID_read(&rfid, RFID_TIMEOUT);
	// stop movement
	motion_stop();

	// read RFID correctly?
	if(err == MI_OK)
	{
		// calculate next movement on the route
		nstate = S_NEXT_MOV;
	}
	else
		// RFID timeout
		// continue to error state
		nstate = S_ERROR;
}

/******************************************************************************
State Next Movement
******************************************************************************/
//uint8_t cross_found_func(void)
//{
//	// calculate next direction of movement
//	//next_move_dir = ...
//
//	return S_ROTATE;
//}
//
//uint8_t room_found_func(void)
//{
//	// check if robot needs to stop in this room
//	// if(quarto paragem)
//		// stop at this room
//		// return S_STOPPED;
//
//	// else, continue to the next rooms
//	return S_FLW_LINE;
//}
//
//// Next move function pointer
//uint8_t (*next_move_func[])(void) = {
//		cross_found_func,
//		room_found_func
//};

static void s_next_mov(void)
{
	write_led(LRED,1);
	write_led(LBLUE,0);
	write_led(LGREEN,0);

	// imaginando que está no quarto pretendido:

//	motion_status = MOT_OFF;
//	timeout_start(PICK_UP_TIMEOUT);
//
//	nstate = S_STOPPED;
//
	//-----------------------------


	next_move_dir = MOVE_LEFT;

	nstate = S_ROTATE;
}

/******************************************************************************
State Rotate
******************************************************************************/
static void s_rotate(void)
{
	uint8_t err;

	write_led(LRED,1);
	write_led(LBLUE,0);
	write_led(LGREEN,1);

	// rotate to direction 'next_move_dir' (POLLING MODE)
	err = lfollower_rotate(next_move_dir, ROTATE_TIMEOUT);

	// rotate has returned error?
	if(err)
		// rotate TIMEOUT
		// rotate was not successfull
		nstate = S_ERROR;
	else
		// turn completed. Restart following line
		nstate = S_FLW_LINE;
}

/******************************************************************************
State Error
******************************************************************************/
static void s_error(void)
{
	write_led(LRED,1);
	write_led(LBLUE,1);
	write_led(LGREEN,0);



	// send error messages
	// ...

//	if(error_timeout)
//	{
//		// shutdown robot
//		// ????
//	}
}

