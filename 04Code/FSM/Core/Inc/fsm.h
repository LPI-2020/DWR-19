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
#define S_STOPPED		0	// Robot stopped. Waiting for interaction
#define S_RECEIVE		1	// Robot is receiving a new route

#define S_FLW_LINE 		2	// Robot is following line
#define S_RD_RFID		3	// Robot detects and reads RFID
#define S_NEXT_MOV		4	// Robot determines next movement to make
#define S_ROTATE		5	// Robot rotates in order to move in other direction

#define S_ERROR			6	// Robot waiting for intervention

/******************************************************************************
FSM Private Defines
******************************************************************************/
// timeouts in seconds
//#define RFID_TIMEOUT	2	// RFID timeout time
//#define ROTATE_TIMEOUT	4	// rotate timeout time
//#define PICK_UP_TIMEOUT 20	// Pick up (of the object in each room) timeout time

// User button debounce
#define USER_BTN_PORT	(GPIOC)
#define USER_BTN_PIN	(GPIO_PIN_8)

extern checkpoint_t route1[4];
extern checkpoint_t *route_ptr;
//extern checkpoint_t *route_base_ptr;

/******************************************************************************
FSM current state pointer
******************************************************************************/
extern void (*fsm_func_ptr[])(void);

extern uint8_t state;
extern uint8_t nstate;
