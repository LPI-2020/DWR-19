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

	//HAL_Delay(500);

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
	//TIM_MOTION.Instance->EGR = TIM_EGR_UG;
}

void motion_stop(void)
{
//	if(motion_status == MOT_OFF)
//		// already stopped
//		return;

	// disable Line Follower
	lfollower_stop();

	if(motion_status == MOT_HOLD)
		// motion in hold
		// stop detectors remain enabled
		return;

	// else, stop sampling motion sensors
	HAL_TIM_Base_Stop_IT(&TIM_MOTION);

	// disable Stop Detectors
	stop_detector_deInit();
	// motion OFF
//	motion_status = MOT_OFF;
}

void motion_isr(void)
{
	uint8_t err;

	// check Stop Sensors
	err = stop_detector_isr();

	if(motion_status == MOT_HOLD)
	{
		if(timeout_flag)
		{
			// motion timeout occured
			motion_status = MOT_TIMEOUT;
			// stop everything
			motion_stop();
			return;
		}
		if(err == 0)
		{
			// obstacle has been moved
			// stop timeout
			timeout_stop();
			// restart movement
			motion_start();
		}
		else
			// continue in Hold
			return;
	}
	else if(err)
	{
		// update motion_status
		// Signal that Motion is stopped due to Stop Mark/Obstacle
		// err = E_CROSS_FOUND (1) -> motion_status = MOT_CROSS_FOUND (2)
		// err = E_OBS_FOUND (2) -> motion_status = MOT_HOLD (3)
		motion_status = err + (MOT_CROSS_FOUND - E_ST_CROSS_FOUND);

		// if motion is on hold, begin timeout
		if(motion_status == MOT_HOLD)
		{
			timeout_start(HOLD_TIMEOUT);
			motion_stop();
			return;
		}

		// obstacle/stop mark found
		// stop movement
//		motion_stop();
//
//		return;
	}

	// line follower ISR
	// continue to follow line
	err = lfollower_isr();
	if(err)
	{
		// signal motion error
		motion_status = MOT_ERR;

		// error following line
		// stop movement
		motion_stop();
	}
}
