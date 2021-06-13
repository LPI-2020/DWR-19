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
Define Peripherals INSTANCES in use
******************************************************************************/
//#include "adc.h"
#include "tim.h"

// used to sample values from Line Follower Sensors to PID
#define TIM_LF_PID 			(htim6)

/******************************************************************************
Define Line Follower Sensors (using QTR)
******************************************************************************/
#include "qtr.h"

// Line Follower RIGHT sensor
#define LF_SENSOR_R 	(SENSOR3)
// Line Follower LEFT sensor
#define LF_SENSOR_L 	(SENSOR6)

/******************************************************************************
Line Follower Error Codes
******************************************************************************/
#define EXIT_SUCCESS	0
#define E_LF_TIMEOUT	4

/******************************************************************************
Line Follower Functions
******************************************************************************/
void lfollower_start(void);
void lfollower_stop(void);
void lfollower_isr();

uint8_t lfollower_rotate(move_dir_e dir);

/******************************************************************************
Debug Functions
******************************************************************************/
// print line follower sensors values
void lfollower_print_sens(void);

#endif // !__LFOLLOWER_H__
