/*
 * route.h
 *
 * Route Module
 *  Created on: 14/06/2021
 */

#ifndef __ROUTE_H__
#define __ROUTE_H__

/******************************************************************************
Checkpoints Definition
******************************************************************************/
// action enum - defines the next move when founds a cross
typedef enum{
	ACT_RIGHT,		// turn right (at a cross)
	ACT_LEFT,		// turn left (at a cross)
	ACT_FORWARD,	// don't stop (at a room)
	ACT_STOP,		// stops (at a room)
	ACT_BACKWARD
} action_e;

// checkpoint struct definition
typedef struct{
	char *RFID;			// RFID: checkpoint unique identifier
	action_e action;	// Action to execute at the checkpoint
} checkpoint_t;

/******************************************************************************
Route Definition
******************************************************************************/
// Route is a list of checkpoints
#define route_t checkpoint_t*

#endif /* _ROUTE_H_ */
