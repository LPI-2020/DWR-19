/*
 * route.h
 *
 * Route Module
 *  Created on: 14/06/2021
 */

#ifndef __ROUTE_H__
#define __ROUTE_H__

/******************************************************************************
Route Definition
******************************************************************************/
// action enum - defines the next move when founds a cross
typedef enum{
	ACT_RIGHT,		// turns right (cross)
	ACT_LEFT,		// turns left (cross)
	ACT_FORWARD,		// don't stop (room)
	ACT_STOP			// stops (room)
} action_e;

// checkpoint struct definition
typedef struct{
	char *RFID;			// RFID: checkpoint unique identifier
	action_e action;	// Action to execute at the checkpoint
} checkpoint_t;

// route_t is a series of checkpoints
typedef checkpoint_t* route_t;


#endif /* _ROUTE_H_ */
