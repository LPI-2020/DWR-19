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
Define Move Speeds (from 0 to 1)
******************************************************************************/
#define FORWARD_SPEED 	(float)(0.78)
#define TURN_SPEED 		(float)(0.7)

// Sum of pid.u and FORWARD_SPEED is calculated by CALC_SPEED
// which give us a command variable used to set a certain speed in each
// motor.
// If speed is not zero, then Motor_Speed will equal to:
//	(Base_Speed + Additional_Speed) which is less or equal to 100 %
//
// i.e: if FORWARD_SPEED=70% and speed=0, then Motor_Speed=70%
//		if FORWARD_SPEED=70% and speed=50%, then
//			Motor_Speed=70+50*(30%), which is 85%
#define CALC_SPEED(_u_) ((FORWARD_SPEED + (_u_) * (1 - FORWARD_SPEED)) * 100)

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
#define KP (float) (1)
#define KI (float) (0.1)
#define KD (float) (0.3)

//static pid_st pid = {
//	.y 			= 0,	// <----
//	.prev_y 	= 0, 	// <------
//	.kp_h 		= KP,
//	.ki_h 		= KI * TIMER6_PERIOD,
//	.kd_h 		= KD * (1 - a_pid) / TIMER6_PERIOD,
//	.error 		= 0,
//	.sum_errors = 0,
//	.prev_error = 0,
//	.u 			= 0,
//	.u_d 		= 0,
//	.prev_u_d 	= 0
//};

static pid_st pid = {
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

#define LAST_ERRORS_SIZE (8)
static float last_errors[LAST_ERRORS_SIZE] = {0};

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
	static float mean_err;

	// Apply PID to adjust motor PWM/velocity
	// error = S_LEFT_VAL - S_RIGHT_VAL
	pid_calcule(&pid, 	DIG_TO_ANALOG(lf_sens[SENSOR_LEFT]),
						DIG_TO_ANALOG(lf_sens[SENSOR_RIGHT]));

	mean_err = mean_window(pid.error, last_errors, LAST_ERRORS_SIZE);

	// according to calculated error = S_LEFT_VAL - S_RIGHT_VAL:
	// command var. LEFT is equal to (+pid.u)
	// command var. RIGHT is equal to (-pid.u)
	move(CALC_SPEED(+pid.u), CALC_SPEED(-pid.u));
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