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
#include "adc.h"
#include "tim.h"

// used to sample values from Line Follower Sensors to PID
#define TIM_LF_PID 			(htim3)

/******************************************************************************
Define Line Follower Sensors
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
#define E_CROSS_FOUND	1
#define E_ROOM_FOUND	2
#define E_OBS_FOUND		3
#define E_LF_TIMEOUT	4

/******************************************************************************
Line Follower Functions
******************************************************************************/
void lfollower_start(void);
void lfollower_stop(void);

void lfollower_pid(void);
uint8_t lfollower_rotate(move_dir_e dir);

uint8_t lfollower_control(void);

/******************************************************************************
Debug Functions
******************************************************************************/
// print line follower sensors values
void lfollower_print_sens(void);

#endif // !__LFOLLOWER_H__
