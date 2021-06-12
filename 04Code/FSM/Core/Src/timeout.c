#include "timeout.h"

/******************************************************************************
Timeout Flags
******************************************************************************/
uint8_t timeout_flag = 0;
//static uint8_t timeout_cycles = 0;

/******************************************************************************
Timeout Private Defines
******************************************************************************/
#define PERIOD_1SEC		(10000)
#define MAX_TIMEOUT		(uint8_t)(65535 / PERIOD_1SEC)

/******************************************************************************
Timeout Start
******************************************************************************/
void timeout_start(uint8_t time_sec)
{
	// update timeout timer reload
	if(time_sec > MAX_TIMEOUT)
	{
//		TIM_TIMEOUTS.Init.Prescaler = x - 1;
		TIM_TIMEOUTS.Init.Period = (PERIOD_1SEC * MAX_TIMEOUT) - 1;
//		timeout_cycles = time_sec ...
	}
	else
		TIM_TIMEOUTS.Init.Period = (PERIOD_1SEC * time_sec) - 1;

	if(HAL_TIM_Base_Init(&TIM_TIMEOUTS) != HAL_OK)
		Error_Handler();
	else
	{
		// start timeout Timer
		HAL_TIM_Base_Start_IT(&TIM_TIMEOUTS);
		timeout_flag = 0;
	}
}

/******************************************************************************
Timeout Stop
******************************************************************************/
void timeout_stop()
{
	// stop timeout Timer
	HAL_TIM_Base_Stop_IT(&TIM_TIMEOUTS);
}

/******************************************************************************
Timeout ISR
******************************************************************************/
void timeout_isr()
{
	// timeout occured
	timeout_flag = 1;
	// stop generating timeouts
	timeout_stop();
}
