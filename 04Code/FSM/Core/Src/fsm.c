/*
 * fsm.c
 *
 * FSM module
 *
 *  Created on: June 3, 2021
 *
 */

#include "fsm.h"

//#include "stop_sensors.h"
//#include "lfollower.h"
//#include "move.h"
#include "motion.h"

//#include "spi.h"
#include "rfid-rc522.h"

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

// Timeout flags
uint8_t pick_up_timeout = 0;
uint8_t obs_found_timeout = 0;
//uint8_t rotate_timeout = 0;
//uint8_t read_rfid_timeout = 0;

// Direction of the next movement at junction
uint8_t next_move_dir = 0;

uint8_t user_btn; //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> define this pin
/******************************************************************************
State Stopped
******************************************************************************/
static void s_stopped(void)
{
	// stop movement
	motion_stop();

	if(route_finished && new_route_incoming)
		// route finished and receiving new route
		nstate = S_RECEIVE;

//	else if((!obs_found_flag) && (!obs_found_timeout))
//		// obstacle is not there anymore and timer not finished
//		// restart movement
//		nstate = S_FLW_LINE;
//
//	else if(obs_found_timeout)
//		// obstacle has been there for too long
//		// continue to error state
//		nstate = S_ERROR;

	else if((!route_finished) && (user_btn || pick_up_timeout))
		// Route not finished and User button pressed or robot has been waiting
		// too much time for user to pick up his goods. Restart movement.
		nstate = S_FLW_LINE;

	// Else, continue in S_STOPPED
}

/******************************************************************************
State Receive
******************************************************************************/
static void s_receive(void)
{
	if(new_route_incoming == 0)
		// new route has been fully received
		nstate = S_STOPPED;

	// Else, continue receiving route
}

/******************************************************************************
State Follow Line
******************************************************************************/
static void s_flw_line(void)
{
	// start movement
	motion_start();

	switch((uint8_t)motion_status)
	{
	case MOT_CROSS_FOUND:
		// Cross Found
		nstate = S_RD_RFID;
		break;
	case MOT_ROOM_FOUND:
		// Room Found
		nstate = S_NEXT_MOV;
		break;
	case MOT_HOLD:
		// obstacle found
		nstate = S_STOPPED;
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

	// start movement
	motion_start();
	// wait for RFID read or 'read_rfid_timeout' (POLLING MODE)
	err = read_RFID(&rfid);
	// stop movement
	motion_stop();

	// read RFID correctly?
	if(err == MI_OK)
		// calculate next movement on the route
		nstate = S_NEXT_MOV;
	else
		// RFID timeout
		// continue to error state
		nstate = S_ERROR;
}

/******************************************************************************
State Next Movement
******************************************************************************/
uint8_t cross_found_func(void)
{
	// clear cross found flag
//	cross_found_flag = 0;

	// calculate next direction of movement
	//next_move_dir = ...

	return S_ROTATE;
}

uint8_t room_found_func(void)
{
	// clear room found flag
//	room_found_flag = 0;

	// check if robot needs to stop in this room
	// if (quarto paragem)
		// stop at this room
		// return S_STOPPED;
	//else
		// continue to the next rooms
		return S_FLW_LINE;
}

// Next move function pointer
uint8_t (*next_move_func[])(void) = {
		cross_found_func,
		room_found_func
};

static void s_next_mov(void)
{
	// This state only gets executed if cross_found_flag or room_found_flag are
	// activated. Therefore, we can determine which next_move_func has to be
	// executed using the value of only one flag, p.e, room_found_flag.
	// Keep in mind that next_move_func must be set allowing that if
	// room_found_flag is 1, next_move_func points to room_found_func.
//	nstate = next_move_func[room_found_flag & 0x01]();
}

/******************************************************************************
State Rotate
******************************************************************************/
static void s_rotate(void)
{
	uint8_t err;

	// rotate to direction 'next_move_dir' (POLLING MODE)
	err = lfollower_rotate(next_move_dir);

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
	// send error messages
	// ...

//	if(error_timeout)
//	{
//		// shutdown robot
//		// ????
//	}
}

