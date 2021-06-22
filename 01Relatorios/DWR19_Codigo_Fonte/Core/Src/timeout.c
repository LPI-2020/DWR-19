/*
 * timeout.c
 *
 * Timeouts Module
 *
 *  Created on: June 12, 2021
 */
#include "timeout.h"

/******************************************************************************
Timeout Start
******************************************************************************/
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
	HAL_TIM_Base_Stop_IT(&TIM_TIMEOUTS);
}

/******************************************************************************
Timeout ISR
******************************************************************************/
//volatile uint8_t num_sec = 0;
volatile uint8_t 	rfid_timeout = 0,
					rotate_timeout = 0,
					pick_up_timeout = 0,
					hold_timeout = 0;

volatile uint8_t rfid_timeout_ctrl = 0,
		rotate_timeout_ctrl = 0,
		pick_timeout_ctrl = 0,
		hold_timeout_ctrl = 0;

volatile uint8_t rfid_num_sec = 0,
		rotate_num_sec = 0,
		pick_num_sec = 0,
		hold_num_sec = 0;

void timeout_isr(void)
{
	rfid_num_sec 	+= rfid_timeout_ctrl;
	rotate_num_sec 	+= rotate_timeout_ctrl;
	pick_num_sec 	+= pick_timeout_ctrl;
	hold_num_sec	+= hold_timeout_ctrl;

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
}
