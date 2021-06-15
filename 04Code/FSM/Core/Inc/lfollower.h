/*
 * lfollower.h
 *
 * Line Follower Module
 *
 *  Created on: June 5, 2021
 */
#ifndef __LFOLLOWER_H__
#define __LFOLLOWER_H__

#include "move.h" // using move_dir_e

/******************************************************************************
Define Line Follower Sensors (using QTR)
******************************************************************************/
#include "qtr.h"

// Define Line Follower Right and Left sensors
#define LF_SENSOR_R 	(SENSOR3)
#define LF_SENSOR_L 	(SENSOR6)

// Define Line Follower Control Sensors (Right and Left)
#define LF_SENSOR_CTR_R	(SENSOR4)
#define LF_SENSOR_CTR_L	(SENSOR5)

/******************************************************************************
Line Follower Error Codes
******************************************************************************/
#define E_LF_OFF			1	// error: line follower disabled
#define E_LF_NO_LINE		5	// error: no line to follow

/******************************************************************************
Line Follower Functions
******************************************************************************/
void lfollower_start(void);
void lfollower_stop(void);
uint8_t lfollower_isr();

uint8_t lfollower_rotate(move_dir_e dir, uint8_t timeout);

/******************************************************************************
Debug Functions
******************************************************************************/
// print line follower sensors values
void lfollower_print_sens(void);

#endif // !__LFOLLOWER_H__
