/*
 * motion.c
 *
 * Motion Module
 *
 *  Created on: June 12, 2021
 */
#include "motion.h"

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
	// enable Stop Detectors
	stop_detector_init();
	// motion ON
	motion_status = MOT_ON;
}

void motion_stop(void)
{
	if(motion_status == MOT_OFF)
		// already stopped
		return;

	// disable Line Follower
	lfollower_stop();
	// disable Stop Detectors
	stop_detector_deInit();
	// motion OFF
	motion_status = MOT_OFF;
}

void motion_isr(void)
{
	uint8_t err;

	// check Stop Sensors
	err = stop_detector_isr();

	// check if there is no error due to Stop Detectors
	if(err)
	{
		// obstacle/stop mark found
		// stop movement
		motion_stop();

		// Signal that Motion is stopped due to Stop Mark/Obstacle
		// err = E_CROSS_FOUND (1) -> motion_status = MOT_CROSS_FOUND (2)
		// err = E_ROOM_FOUND (2) -> motion_status = MOT_ROOM_FOUND (3)
		// err = E_OBS_FOUND (3) -> motion_status = MOT_HOLD (4)
		motion_status = err + (MOT_CROSS_FOUND - E_ST_CROSS_FOUND);
		// force exit
		return;
	}

	// no error
	// continue to follow line
	err = lfollower_isr();
	if(err)
	{
		// error following line
		// stop movement
		motion_stop();
		// signal motion error
		motion_status = MOT_ERR;
	}
}
