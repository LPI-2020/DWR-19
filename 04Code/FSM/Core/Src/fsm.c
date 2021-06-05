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
static void s_room(void);
static void s_rd_rfid(void);
static void s_rotate(void);
static void s_wait(void);
static void s_error(void);

/******************************************************************************
FSM current state pointer
******************************************************************************/
void (*fsm_func_ptr[])(void) = {
		s_stopped,
		s_receive,
		s_flw_line,
		s_room,
		s_rd_rfid,
		s_rotate,
		s_wait,
		s_error
};

uint8_t state = 0;
uint8_t nstate = 0;

/******************************************************************************
State Stopped
******************************************************************************/
static void s_stopped(void)
{
	nstate = S_STOPPED;
}

/******************************************************************************
State Receive
******************************************************************************/
static void s_receive(void)
{
	nstate = S_FLW_LINE;
}

/******************************************************************************
State Follow Line
******************************************************************************/
static void s_flw_line(void)
{
	//....

		if(obs_found_flag)
		{
			// Obstacle Found
			nstate = S_WAIT;
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

