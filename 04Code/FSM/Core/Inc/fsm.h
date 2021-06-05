/*
 * fsm.h
 *
 *  Created on: June 3, 2021
 */

/******************************************************************************
FSM states
******************************************************************************/
#define S_STOPPED		0
#define S_RECEIVE		1
#define S_FLW_LINE 		2
#define S_ROOM			3
#define S_RD_RFID		4
#define S_ROTATE		5
#define S_WAIT			6
#define S_ERROR			7

/******************************************************************************
FSM current state pointer
******************************************************************************/
extern void (*fsm_func_ptr[])(void);

extern uint8_t state;
extern uint8_t nstate;
