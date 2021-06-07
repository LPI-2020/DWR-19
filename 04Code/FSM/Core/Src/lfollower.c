/*
 * lfollower.c
 *
 * Line Follower Module
 *
 *  Created on: June 5, 2021
 */
#include "lfollower.h"
#include "pid.h"
#include "move.h"

#include "auxiliares.h" // DIG_TO_ANALOG macro

/******************************************************************************
Define Line Follower Sensors in use
******************************************************************************/
// Line Follower Sensor
static uint32_t lf_sens[2];

// Sensor elements
typedef enum { SENSOR_RIGHT, SENSOR_LEFT } sensor_e;

/******************************************************************************
Define PID parameters to be used
******************************************************************************/
static pid_st pid = {
	.y 			= 0,	// <----
	.prev_y 	= 0, 	// <------
	.kp_h 		= KP,
	.ki_h 		= KI * TIMER6_PERIOD,
	.kd_h 		= KD * (1 - a_pid) / TIMER6_PERIOD,
	.error 		= 0,
	.sum_errors = 0,
	.prev_error = 0,
	.u 			= 0,
	.u_d 		= 0,
	.prev_u_d 	= 0
};

/******************************************************************************
Line Follower Start

@brief	Starts line follower process.
@param	none
@retval	none
******************************************************************************/
void lfollower_start(void)
{
	// start storing Line Follower Sensor values
	HAL_ADC_Start_DMA(&ADC_DMA_INSTANCE, lf_sens, 2);
	// start sampling for PID application
	HAL_TIM_Base_Start_IT(&TIM_PID_SAMPLING);
	// start movement
	move_start();
}

/******************************************************************************
Line Follower PID

@brief	Applies PID algorithm to obtain movement speed required to follow the
		line.
@param	none
@retval	none
******************************************************************************/
void lfollower_pid(void)
{
	// Apply PID to adjust motor PWM/velocity
	// RIGHT SENSOR is used as REFERENCE. i.e: error = S_RIGHT_VAL - S_LEFT_VAL
	pid_calcule(&pid, 	DIG_TO_ANALOG(lf_sens[SENSOR_RIGHT]),
						DIG_TO_ANALOG(lf_sens[SENSOR_LEFT]));

	// Move forward with speed equal to pid.u (%)
	move_forward(pid.u);
}

/******************************************************************************
Line Follower Stop

@brief 	Stops line follower process.
@param	none
@retval	none
******************************************************************************/
void lfollower_stop(void)
{
	// stop storing Line Follower Sensor values
	HAL_ADC_Stop_DMA(&ADC_DMA_INSTANCE);
	// stop sampling for PID application
	HAL_TIM_Base_Stop_IT(&TIM_PID_SAMPLING);
	// stop movement
	move_stop();
}