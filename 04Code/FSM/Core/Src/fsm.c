/*
 * fsm.c
 *
 * FSM module
 *
 *  Created on: June 3, 2021
 *
 */

#include "fsm.h"

#include "stop_sensors.h"
#include "lfollower.h"
#include "move.h"

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

uint8_t stop_err = 0;

// Route finished flag
uint8_t route_finished = 0;
// New route incoming flag
uint8_t new_route_incoming = 0;

// Timeout flags
uint8_t pick_up_timeout = 0;
uint8_t obs_found_timeout = 0;
uint8_t rotate_timeout = 0;
uint8_t read_rfid_timeout = 0;

// Direction of the next movement at junction
uint8_t next_move_dir = 0;

uint8_t user_btn; //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> define this pin
/******************************************************************************
State Stopped
******************************************************************************/
static void s_stopped(void)
{
	if(route_finished && new_route_incoming)
		// route finished and receiving new route
		nstate = S_RECEIVE;

	else if((!obs_found_flag) && (!obs_found_timeout))
		// obstacle is not there anymore and timer not finished
		// restart movement
		nstate = S_FLW_LINE;

	else if(obs_found_timeout)
		// obstacle has been there for too long
		// continue to error state
		nstate = S_ERROR;

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
	uint8_t err;

	err = lfollower_control();

	switch(err)
	{
		case E_CROSS_FOUND:
			// Cross Found
			stop_err = E_CROSS_FOUND;
			nstate = S_RD_RFID;
			break;
		case E_ROOM_FOUND:
			// Room Found
			stop_err = E_ROOM_FOUND;
			nstate = S_NEXT_MOV;
			break;
		case E_OBS_FOUND:
			// Obstacle Found
			nstate = S_STOPPED;
			break;
	}
}

/******************************************************************************
State Read RFID
******************************************************************************/
uint8_t read_RFID(void)
{
	// RFID status reading
	int status;

	uint8_t CardID[4];
	uint8_t type;
  	char *result;

  	// return val: initialized as return not successfull
  	uint8_t retval = 1;

  	// enable RFID reader
  	RFID_RC522_Init();

	do
	{
		status = TM_MFRC522_Check(CardID, &type);

		if (status == MI_OK)
		{
			bin_to_strhex((unsigned char *)CardID, sizeof(CardID), &result);
			// return successful
			retval = 0;
		}
	} while((status != MI_OK) && (!read_rfid_timeout));

	return retval;
}

static void s_rd_rfid(void)
{
	uint8_t err;

	// start movement
	move_forward(RD_RFID_SPEED);

	// wait for RFID read or 'read_rfid_timeout'
	err = read_RFID();
	// stop movement
	move_stop();

	// read RFID correctly?
	if(err == 0)
		// calculate next movement on the route
		nstate = S_NEXT_MOV;
	else
		// continue to error state
		nstate = S_ERROR;
}

uint8_t cross_found_func(void)
{
	stop_err = 0;

	//... do something next_move_dir = ...

	return S_ROTATE;
}

uint8_t room_found_func(void)
{
	stop_err = 0;

	// if (quarto paragem)
		// return S_STOPPED;
	//else
		return S_FLW_LINE;
}

uint8_t (*next_move_func[])(void) = {
		cross_found_func,
		room_found_func
};

/******************************************************************************
State Next Movement
******************************************************************************/
static void s_next_mov(void)
{
	nstate = next_move_func[(stop_err - 1) & 0x01]();
}

/******************************************************************************
State Rotate
******************************************************************************/
static void s_rotate(void)
{
	uint8_t rotate_err;

	// rotate to direction 'next_move_dir'
	rotate_err = lfollower_rotate(next_move_dir);

	// rotate was returned error? (Due to timeout)
	if(rotate_err)
		// rotate was not successfull
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

