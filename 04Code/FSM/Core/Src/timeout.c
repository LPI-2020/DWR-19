/*
 * timeout.c
 *
 * Timeouts Module
 *
 *  Created on: June 12, 2021
 */
#include "timeout.h"

/******************************************************************************
Timeout Private Defines
******************************************************************************/
#define PERIOD_1SEC		(1800)
#define MAX_TIMEOUT		(uint8_t)(65535 / PERIOD_1SEC)

/******************************************************************************
Timeout Flags
******************************************************************************/
uint8_t timeout_flag = 0;
//static uint8_t timeout_cycles = 0;

/******************************************************************************
Timeout Start
******************************************************************************/
void timeout_start(int time_sec)
{
	// update timeout timer reload
	if(time_sec > MAX_TIMEOUT)
	{
//		TIM_TIMEOUTS.Init.Prescaler = x - 1;
		TIM_TIMEOUTS.Init.Period = (PERIOD_1SEC * MAX_TIMEOUT) - 1;
//		timeout_cycles = time_sec ...
	}
	else
		TIM_TIMEOUTS.Init.Period = (PERIOD_1SEC * time_sec) - 1; // >>>>>>>>>>>>> check this

	// init Timer
	if(HAL_TIM_Base_Init(&TIM_TIMEOUTS) != HAL_OK)
		// init error
		Error_Handler();
	else
	{
		// init timer ok
		// reset timeout flag
		timeout_flag = 0;

		// clear TIM_SR_UIF TIM flag
		__HAL_TIM_CLEAR_FLAG(&TIM_TIMEOUTS, TIM_SR_UIF);
		// start timeout Timer
		HAL_TIM_Base_Start_IT(&TIM_TIMEOUTS);
	}
}

/******************************************************************************
Timeout Stop
******************************************************************************/
void timeout_stop(void)
{
	// stop timeout Timer
	HAL_TIM_Base_Stop_IT(&TIM_TIMEOUTS);
}

/******************************************************************************
Timeout ISR
******************************************************************************/
void timeout_isr(void)
{
	// set timeout flag
	timeout_flag = 1;
	// stop generating timeouts
	timeout_stop();
}
