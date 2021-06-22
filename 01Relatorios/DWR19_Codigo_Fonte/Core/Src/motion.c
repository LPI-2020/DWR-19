/*
 * motion.c
 *
 * Motion Module
 *
 *  Created on: June 12, 2021
 */
#include "motion.h"

#include "timeout.h"
#include "lfollower.h"
#include "stop_sensors.h"

/******************************************************************************
Motion Status
******************************************************************************/
// Current Motion Status
motion_status_e motion_status = MOT_OFF;

/******************************************************************************
Motion Functions
******************************************************************************/
void motion_start(void)
{
	if(motion_status == MOT_ON)
		// already moving
		return;

	// enable Line Follower
	lfollower_start();

	// start movement before beeing on Hold
	if(motion_status == MOT_HOLD)
	{
		// motion ON
		motion_status = MOT_ON;
		return;
	}

	// motion ON
	motion_status = MOT_ON;
	// enable Stop Detectors
	stop_detector_init();

	// start sampling motion sensors
	HAL_TIM_Base_Start_IT(&TIM_MOTION);
}

void motion_stop(void)
{
	// disable Line Follower
	lfollower_stop();

	if(motion_status == MOT_HOLD)
		// motion in hold
		// stop detectors remain enabled
		return;

	// disable Stop Detectors
	stop_detector_deInit();

	// else, stop sampling motion sensors
	HAL_TIM_Base_Stop_IT(&TIM_MOTION);
}

#include "tests.h"
void motion_isr(void)
{
	uint8_t err;

	// check Stop Sensors
	err = stop_detector_isr();

	if(motion_status == MOT_HOLD)
	{
		// obstacle timeout?
		if(hold_timeout)
		{
			//timeout_flag = 0;
			hold_timeout = 0;
			// motion timeout occured
			motion_status = MOT_TIMEOUT;
			return;
		}
		// obstacle not there?
		if(err == 0)
		{
			// obstacle has been moved
			// stop timeout
			hold_timeout_ctrl = 0;
			hold_num_sec = 0;

			// restart movement
			motion_status = MOT_OK;
			return;
		}

		// continue in Hold
		return;
	}
	// obstacle detected?
	else if(err == E_ST_OBS_FOUND)
	{
		motion_status = MOT_HOLD;
		// start timeout
		hold_timeout_ctrl = 1;
		return;
	}
	// cross detected?
	else if(err == E_ST_CROSS_FOUND)
		motion_status = MOT_CROSS_FOUND;

	// line follower ISR
	// continue to follow line
	err = lfollower_isr();
	if(err)
		// signal motion error
		motion_status = MOT_ERR;
}
