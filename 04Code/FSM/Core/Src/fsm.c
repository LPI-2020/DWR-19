/*
 * fsm.c
 *
 * FSM module
 *
 *  Created on: June 3, 2021
 */

#include "stop_sensors.h"
#include "lfollower.h"

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

// Current FSM state
uint8_t state = 0;
// Next FSM state
uint8_t nstate = 0;

uint8_t route_finished = 0;
uint8_t new_route_incoming = 0;

uint8_t pick_up_timeout = 0;
uint8_t obs_found_timeout = 0;
uint8_t rotate_timeout = 0;


/******************************************************************************
State Stopped
******************************************************************************/
static void s_stopped(void)
{
	if(route_finished && new_route_incoming)
		// route finished and receiving new route
		nstate = S_RECEIVE;
	else if(obs_found_timeout)
		// obstacle has been there for too long
		nstate = S_ERROR;
	else if((route_finished == 0) && (user_btn || pick_up_timeout))
		// route not finished and User button pressed
		nstate = S_FLW_LINE;
	//else
	//	nstate = S_STOPPED;

	// Else, continue in the same state
}

/******************************************************************************
State Receive
******************************************************************************/
static void s_receive(void)
{
	// new route has been fully received?
	if(new_route_incoming == 0)
		nstate = S_STOPPED;
	//else
	//	nstate = S_RECEIVE;

	// Else, continue receiveing route
}

/******************************************************************************
State Follow Line
******************************************************************************/
static void s_flw_line(void)
{
	// obstacle detected?
	if(obs_found_flag)
	{
		// Obstacle Found
		// enables timer counting OBS_TIM_ seconds
		nstate = S_STOPPED;
	}
	if(cross_found_flag)
	{
		// Cross Found
		nstate = S_RD_RFID;
	}
	if(room_found_flag)
	{
		// Room Found
		nstate = S_ROOM;

	}


}

/******************************************************************************
State Room
******************************************************************************/
static void s_room(void)
{
	nstate = S_FLW_LINE;
}

/******************************************************************************
State Read RFID
******************************************************************************/
static void s_rd_rfid(void)
{
	nstate = S_ROTATE;
}

/******************************************************************************
State Rotate
******************************************************************************/
static void s_rotate(void)
{
	nstate = S_FLW_LINE;
}

/******************************************************************************
State Wait
******************************************************************************/
static void s_wait(void)
{
	nstate = S_ERROR;
}

/******************************************************************************
State Error
******************************************************************************/
static void s_error(void)
{
	nstate = S_FLW_LINE;
}

