#include "motion.h"

#include "lfollower.h"
#include "stop_sensors.h"

/******************************************************************************
Motion Status
******************************************************************************/
// Current Motion Status
motion_status_e motion_status = MOT_OFF;

/******************************************************************************

******************************************************************************/
void motion_start(void)
{
	// enable Line Follower
	lfollower_start();
	// enable Stop Detectors
	stop_detector_init();
	// motion OFF
	motion_status = MOT_ON;
}

void motion_stop(void)
{
	// disable Line Follower
	lfollower_stop();
	// disable Stop Detectors
	stop_detector_deInit();
	// motion ON
	motion_status = MOT_OFF;
}

void motion_isr(void)
{
	uint8_t err;

	// check Stop Sensors
	err = stop_detector_isr();

	// check if there is no error due to Stop Detectors
	if(err == 0)
		// no error
		// continue to follow line
		lfollower_isr();
	else
	{
		// obstacle/stop mark found
		// stop line follower
		lfollower_stop();
		// Signal Motion stopped due to Stop Mark/Obstacle
		motion_status = err + (MOT_CROSS_FOUND - E_CROSS_FOUND);
	}
}
