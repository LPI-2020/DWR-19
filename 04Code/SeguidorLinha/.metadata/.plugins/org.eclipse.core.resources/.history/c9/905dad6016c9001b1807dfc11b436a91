/*
 * lfollower.h
 *
 * Line Follower Module
 *
 *  Created on: June 5, 2021
 */
#ifndef __LFOLLOWER_H__
#define __LFOLLOWER_H__

/******************************************************************************
Define Peripherals in use
******************************************************************************/
#include "adc.h"
#include "tim.h"

#define ADC_DMA_INSTANCE (hadc1)	// used to store Sensors values
#define TIM_PID_SAMPLING (htim6)	// used to sample values to PID

/******************************************************************************
Line Follower Functions
******************************************************************************/
void lfollower_start(void);
void lfollower_stop(void);

void lfollower_pid(void);

#endif // !__LFOLLOWER_H__
