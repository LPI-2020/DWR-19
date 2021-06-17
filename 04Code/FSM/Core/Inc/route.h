/*
 * route.h
 *
 * Route Module
 *  Created on: 14/06/2021
 */

#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "stdint.h" // using uint8_t
#include "move.h"	// using move enums

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
//	move_dir_e dir;			// Direction to take at the checkpoint
	action_e action;	// Action to execute at the checkpoint
} checkpoint_t;

// route_t is a series of checkpoints
typedef checkpoint_t* route_t;


#endif /* _ROUTE_H_ */
