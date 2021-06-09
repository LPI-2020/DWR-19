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

// ADC DMA linked to Line Follower Sensors
#define ADC_LF_SENS_DMA 	(hadc1)
// used to sample values from Line Follower Sensors to PID
#define TIM_LF_SENS_PID 	(htim6)
// used to timeout lfollower rotate
#define TIM_LF_ROTATE		(TIM_TIMEOUTS)

/******************************************************************************
Line Follower Functions
******************************************************************************/
void lfollower_start(void);
void lfollower_stop(void);

void lfollower_pid(void);
uint8_t lfollower_rotate(move_dir_e dir);

/******************************************************************************
Debug Functions
******************************************************************************/
#ifdef _DEBUG_
#include "usart.h"
#include <stdio.h>

// print line follower sensors values
void lfollower_print_sens(void);
#endif // !_DEBUG_

#endif // !__LFOLLOWER_H__
