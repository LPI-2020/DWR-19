/*
 * fsm.h
 *
 * FSM module
 *
 *  Created on: June 3, 2021
 */

#include <stdint.h> // using uint8_t
#include "route.h"

/******************************************************************************
FSM states
******************************************************************************/
typedef enum
{
	S_STOPPED = 0,	// Robot stopped. Waiting for interaction
	S_RECEIVE,		// Robot is receiving a new route

	S_FLW_LINE,		// Robot is following line
	S_RD_RFID,		// Robot detects and reads RFID

	S_NEXT_MOV,		// Robot determines next movement to make
	S_ROTATE,		// Robot rotates in order to move in other direction

	S_ERROR			// Robot waiting for intervention
} state_e;

/******************************************************************************
FSM Private Defines
******************************************************************************/
// User button debounce
#define USER_BTN_PORT	(GPIOC)
#define USER_BTN_PIN	(GPIO_PIN_8)

// define number of routes created
#define NUM_ROUTES		(2)

// list of routes
extern route_t route_arr[NUM_ROUTES];
// current route
extern checkpoint_t *route_ptr;

extern int remote_ctrl_dir;

/******************************************************************************
FSM current state pointer
******************************************************************************/
extern void (*fsm_func_ptr[])(void);

extern state_e state;
extern state_e nstate;
