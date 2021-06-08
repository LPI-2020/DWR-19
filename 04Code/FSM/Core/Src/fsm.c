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

/******************************************************************************
FSM flags
******************************************************************************/
// Current FSM state
uint8_t state = 0;
// Next FSM state
uint8_t nstate = 0;

// Route finished flag
uint8_t route_finished = 0;
// New route incoming flag
uint8_t new_route_incoming = 0;

// Stop sensors flags
uint8_t pick_up_timeout = 0;
uint8_t obs_found_timeout = 0;
uint8_t rotate_timeout = 0;

// Direction of the next movement at junction
uint8_t next_move_dir = 0;

/******************************************************************************
State Stopped
******************************************************************************/
static void s_stopped(void)
{
	if(route_finished && new_route_incoming)
		// route finished and receiving new route
		nstate = S_RECEIVE;

	else if((!obs_found_flag) && (!obs_found_timeout))
	{
		// obstacle is not there anymore and timer not finished
		// restart movement
		nstate = S_FLW_LINE;
		// enable line follower
		lfollower_start();
	}

	else if(obs_found_timeout)
		// obstacle has been there for too long
		// continue to error state
		nstate = S_ERROR;

	else if((!route_finished) && (user_btn || pick_up_timeout))
	{
		// Route not finished and User button pressed or robot has been waiting
		// too much time for user to pick up his goods. Restart movement.
		nstate = S_FLW_LINE;
		// enable line follower
		lfollower_start();
	}

	// Else, continue in S_STOPPED
}

/******************************************************************************
State Receive
******************************************************************************/
static void s_receive(void)
{
	if(new_route_incoming == 0)
	{
		// new route has been fully received
		nstate = S_STOPPED;
		// stop line follower
		//lfollower_stop();
	}
	// Else, continue receiving route
}

/******************************************************************************
State Follow Line
******************************************************************************/
static void s_flw_line(void)
{
	// obstacle detected?
	if(obs_found_flag)
	{
		// enables timer counting OBS_TIM seconds
		// ....
		nstate = S_STOPPED;
		// stop line follower
		lfollower_stop();
	}
	if(cross_found_flag)
	{
		// Cross Found
		nstate = S_RD_RFID;
		// stop line follower
		lfollower_stop();
	}
	if(room_found_flag)
	{
		// Room Found
		nstate = S_NEXT_MOV;
		// stop line follower
		lfollower_stop();
	}

}

/******************************************************************************
State Read RFID
******************************************************************************/
static void s_rd_rfid(void)
{
	// move forward until RFID card is in range of RFID detector
	move_forward(0.6);
	HAL_Delay(500);
	move_stop();

	// read RFID
	// ...

	// calculate next movement on the route
	nstate = S_NEXT_MOV;
}

/******************************************************************************
State Next Movement
******************************************************************************/
static void s_next_mov(void)
{

	// next_move_dir = ...
	nstate = S_FLW_LINE;
}

/******************************************************************************
State Rotate
******************************************************************************/
static void s_rotate(void)
{
	// rotate to 'next_move_dir' with speed ROTATE_SPEED
	move_rotate(next_move_dir, ROTATE_SPEED);

	// if rotate RIGHT, stop rotate when right sensor is over the line.
	// if rotate LEFT, stop rotate when left sensor is over the line.

	//while(((!SENSOR4) || rotate_timeout)
	//	;

	if(rotate_timeout)
		// rotate not successfull
		nstate = S_ERROR;
	else
	{
		// turn completed. Restart following line
		nstate = S_FLW_LINE;
		// enable line follower
		lfollower_start();
	}
}

/******************************************************************************
State Error
******************************************************************************/
static void s_error(void)
{
	// send error messages
	// ...

//	if(error_timeout)
//	{
//		// shutdown robot
//		// ????
//	}
}

