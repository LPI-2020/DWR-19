/*
 * fsm.h
 *
 * FSM module
 *
 *  Created on: June 3, 2021
 */

/******************************************************************************
FSM states
******************************************************************************/
#define S_STOPPED		0	// Robot stopped. Waiting for interaction
#define S_RECEIVE		1	// Robot is receiving a new route

#define S_FLW_LINE 		2	// Robot is following line
#define S_RD_RFID		4	// Robot detects and reads RFID
#define S_NEXT_MOV		5	// Robot determines next movement to make
#define S_ROTATE		6	// Robot rotates in order to move in other direction

#define S_ERROR			7	// Robot waiting for intervention

/******************************************************************************
FSM Private Defines
******************************************************************************/
//#define OBS_TIM

// defines speed of rotation
#define ROTATE_SPEED 0.6

#define SENSOR4 (000) // >>>>>>>>>>>>>>> define this
#define SENSOR5 (000)

/******************************************************************************
FSM current state pointer
******************************************************************************/
extern void (*fsm_func_ptr[])(void);

extern uint8_t state;
extern uint8_t nstate;
