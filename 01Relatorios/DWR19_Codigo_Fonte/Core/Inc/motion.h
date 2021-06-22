/*
 * motion.h
 *
 * Motion Module
 *
 *  Created on: June 12, 2021
 */
#ifndef __MOTION_H__
#define __MOTION_H__

/******************************************************************************
Motion Peripherals
******************************************************************************/
#include "tim.h"
// Used to apply PID algorythm and Stop sensors ISRs
#define TIM_MOTION 			(htim6)

/******************************************************************************
Motion Status
******************************************************************************/
typedef enum
{
	MOT_ON = 0,			// Motion ON (moving)
	MOT_OFF,			// Motion OFF (stopped)
	MOT_OK,				// Motion OK

	MOT_CROSS_FOUND,	// Motion: stopped at a cross
	MOT_HOLD,			// Motion in Hold (obstacle detected)

	MOT_ERR,			// Motion Error (Out of route)
	MOT_TIMEOUT			// Motion Timeout - too much time in MOTION_HOLD
} motion_status_e;

// Current Motion Status
extern motion_status_e motion_status;

/******************************************************************************
Motion Functions
******************************************************************************/
void motion_start(void);
void motion_stop(void);
void motion_isr(void);

#endif // !__MOTION_H__
