/*
 * timeout.c
 *
 * Timeouts Module
 *
 *  Created on: June 12, 2021
 */
#include "timeout.h"
#include "tests.h"

/******************************************************************************
Timeout Private Defines
******************************************************************************/
#define PERIOD_1SEC		(1800)
#define MAX_TIMEOUT		(uint8_t)(65535 / PERIOD_1SEC)

/******************************************************************************
Timeout Flags
******************************************************************************/
//volatile uint8_t timeout_flag = 0;

/******************************************************************************
Timeout Start
******************************************************************************/
//void timeout_start(int time_sec)
//{
//	// update timeout timer reload
//	if(time_sec > MAX_TIMEOUT)
//		TIM_TIMEOUTS.Init.Period = (PERIOD_1SEC * MAX_TIMEOUT) - 1;
//	else
//		TIM_TIMEOUTS.Init.Period = (PERIOD_1SEC * time_sec) - 1;
//
//	// init Timer
//	if(HAL_TIM_Base_Init(&TIM_TIMEOUTS) != HAL_OK)
//		// init error
//		Error_Handler();
//	else
//	{
//		// init timer ok
//		// reset timeout flag
////		timeout_flag = 0;
//		write_led(LRED, 1);
//		write_led(LBLUE, 1);
//
//		// clear TIM_SR_UIF TIM flag
//		__HAL_TIM_CLEAR_FLAG(&TIM_TIMEOUTS, TIM_SR_UIF);
//		// start timeout Timer
//		HAL_TIM_Base_Start_IT(&TIM_TIMEOUTS);
//	}
//}

void timeout_start(void)
{
	// clear TIM_SR_UIF TIM flag
	__HAL_TIM_CLEAR_FLAG(&TIM_TIMEOUTS, TIM_SR_UIF);
	// start timeout Timer
	HAL_TIM_Base_Start_IT(&TIM_TIMEOUTS);
}
/******************************************************************************
Timeout Stop
******************************************************************************/
void timeout_stop(void)
{
	// stop timeout Timer
	write_led(LRED, 0);
	HAL_TIM_Base_Stop_IT(&TIM_TIMEOUTS);
}

/******************************************************************************
Timeout ISR
******************************************************************************/
volatile uint8_t num_sec = 0;
volatile uint8_t 	rfid_timeout = 0,
					rotate_timeout = 0,
					pick_up_timeout = 0,
					hold_timeout = 0;

uint8_t rfid_timeout_ctrl = 0,
		rotate_timeout_ctrl = 0,
		pick_timeout_ctrl = 0,
		hold_timeout_ctrl = 0;

volatile uint8_t rfid_num_sec = 0,
		rotate_num_sec = 0,
		pick_num_sec = 0,
		hold_num_sec = 0;

void timeout_isr(void)
{
//	num_sec++;
	rfid_num_sec += rfid_timeout_ctrl;
	rotate_num_sec += rotate_timeout_ctrl;
	pick_num_sec += pick_timeout_ctrl;
	hold_num_sec += hold_timeout_ctrl;

	if(rfid_num_sec == RFID_TIMEOUT)
	{
		rfid_timeout = 1;
		rfid_num_sec = 0;
		rfid_timeout_ctrl = 0;
	}

	if(rotate_num_sec == ROTATE_TIMEOUT)
	{
		rotate_timeout = 1;
		rotate_num_sec = 0;
		rotate_timeout_ctrl = 0;
	}

	if(pick_num_sec == PICK_UP_TIMEOUT)
	{
		pick_up_timeout = 1;
		pick_num_sec = 0;
		pick_timeout_ctrl = 0;
	}

	if(hold_num_sec == HOLD_TIMEOUT)
	{
		hold_timeout = 1;
		hold_num_sec = 0;
		hold_timeout_ctrl = 0;
	}

//
//	toggle_led(LBLUE);
//	// set timeout flag
//	timeout_flag = 1;
//	// stop generating timeouts
//	timeout_stop();
}
