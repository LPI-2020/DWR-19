/*
 * lfollower.c
 *
 * Line Follower Module
 *
 *  Created on: June 5, 2021
 */
#include "lfollower.h"
#include "pid.h"
#include "timeout.h"
#include "errors.h"

#include <math.h> // using fabs()

/******************************************************************************
Define Debug Symbol
******************************************************************************/
#define _DEBUG_

#ifdef _DEBUG_
#include "usart.h" // debug
#include <stdio.h>
#endif // !_DEBUG_

/******************************************************************************
Define Move Speeds (from 0 to 1)
******************************************************************************/
#define FORWARD_SPEED 	(float)(0.68)
#define TURN_SPEED 		(float)(0.75)

/******************************************************************************
 * GET_SPEED macro
 *
 * Sum of pid.u and FORWARD_SPEED is calculated by CALC_SPEED
 * which give us a command variable used to set a certain speed in each
 * motor.
 *
 * If speed is not zero, then Motor_Speed will equal to:
 *	(Base_Speed + Additional_Speed) which is less or equal to 100 %
 *
 * i.e: if FORWARD_SPEED=70% and speed=0, then Motor_Speed=70%
 *		if FORWARD_SPEED=70% and speed=50%, then
 *			Motor_Speed=70+50*(30%), which is 85%
*******************************************************************************
Define Type of Speed Calculus
******************************************************************************/
#define GET_SPEED(_u_) (FORWARD_SPEED + (_u_) * (1 - FORWARD_SPEED))

/******************************************************************************
Line Follower Private Flags
******************************************************************************/
// line follower status (enabled 1 or disabled 0)
volatile uint8_t lfollower_status = 0;

/******************************************************************************
Line Follower Start

@brief	Starts line follower process.
@param	none
@retval	none
******************************************************************************/
void lfollower_start(void)
{
	// line follower already enabled?
	if(lfollower_status == 1)
		return;

	// start storing QTR Sensor values
	qtr_init();
	// start movement
	move_start();

	// mark line follower is enabled
	lfollower_status = 1;
}

/******************************************************************************
Line Follower Stop

@brief 	Stops line follower process.
@param	none
@retval	none
******************************************************************************/
void lfollower_stop(void)
{
	// line follower already disabled?
	if(lfollower_status == 0)
		return;

	// stop storing QTR sensor values
	qtr_kill();
	// stop movement
	move_stop();

	// mark line follower is disabled
	lfollower_status = 0;
}

/******************************************************************************
Line Follower ISR

@brief	Applies PID algorithm to obtain movement speed required to follow the
		line.
@param	none
@retval	none
******************************************************************************/
/******************************************************************************
Define PID parameters to be used
******************************************************************************/
#define KP (float) (1.05)
#define KI (float) (0.35)
#define KD (float) (0.013)

static pid_st pid = {
	.kp_h 		= KP,
	.ki_h 		= KI * TIMER6_PERIOD,
	.kd_h 		= KD * (1 - A_PID) / TIMER6_PERIOD,

	.error 		= 0,
	.prev_error = 0,
	.sum_errors = 0,

	.u_d 		= 0,
	.prev_u_d 	= 0,

	.u			= 0,
	.u_sat_a	= +1.0,
	.u_sat_b	= -1.0
};

/******************************************************************************
Line Follower ISR
******************************************************************************/
uint8_t lfollower_isr(void)
{
	if(lfollower_status == 0)
		// line follower is disabled
		return E_LF_OFF;

	if((qtr_get_digital(LF_SENSOR_CTR_R) == 0) &&
		(qtr_get_digital(LF_SENSOR_CTR_L) == 0) &&
		(qtr_get_digital(LF_SENSOR_L) == 0) &&
		(qtr_get_digital(LF_SENSOR_R) == 0))
	{
		// robot is not over the line
		// stop line follower
		lfollower_stop();
		// send error: no line to follow
		return E_LF_NO_LINE;
	}

	// else, robot over the line
	// use PID to obtain PWM values to use on motors
	// error = S_LEFT_VAL - S_RIGHT_VAL
	pid_calcule(&pid, qtr_get_analog(LF_SENSOR_L), qtr_get_analog(LF_SENSOR_R));

	// Apply PID to adjust motor PWM/velocity
	move_control(GET_SPEED(-pid.u), GET_SPEED(+pid.u));

	return EXIT_SUCCESS;
}

/******************************************************************************
Line Follower Rotate

@brief 	Rotates the robot to 'dir' direction, stopping when sensor founds the line
@param	dir - direction to rotate
@retval '1' if timeout occured
******************************************************************************/
uint8_t lfollower_rotate(move_dir_e dir)
{
	// start movement and rotate to 'dir' at speed equal to TURN_SPEED
	move_rotate(dir, TURN_SPEED);
	// start rotate 4second timeout
	rotate_timeout_ctrl = 1;
	// start storing QTR sensor values
	qtr_init();

	// if dir == MOVE_RIGHT, check when SENSOR1 is over the line
	// if dir == MOVE_LEFT, check when SENSOR8 is over the line

	// dir can be -1 (MOVE_RIGHT) or +1 (MOVE_LEFT)
	dir += 1;
	// dir is now 0 or 2
	dir >>= 1;
	// dir is now 0 (MOVE_RIGHT) or 1 (MOVE_LEFT)
	// so, if: 	dir = 0 					-> SENSOR1
	//			dir = 1* (QTR_SENS_NUM - 1) -> SENSOR8 (last sensor)
	//while((qtr_get_digital(dir * (QTR_SENS_NUM - 1)) == 0) && (timeout_flag == 0))
	while((qtr_get_digital(dir * (QTR_SENS_NUM - 1)) == 0) && (rotate_timeout == 0))
		;

	// stop rotating
	move_stop();
	// stop storing QTR sensor values
	qtr_kill();

	// if timeout occured, then we must return an error code, signaling a
	// non successful rotate
	if(rotate_timeout)
	{
		rotate_timeout = 0;
		return E_TIMEOUT;
	}

	// stop timeout
	rotate_timeout_ctrl = 0;
	rotate_num_sec = 0;
	// if timeout didnt occurred then rotate was completed
	return EXIT_SUCCESS;
}

/******************************************************************************
Debug Functions

@brief 	Prints Line Follower Sensors Values
@param	none
@retval	none
******************************************************************************/
#ifdef _DEBUG_

const static uint8_t lf_sens_str[][3] =
{
		"S1",
		"S3",
		"S4",
		"S5",
		"S6",
		"S8"
};

void lfollower_print_sens(void)
{
	char str[32];

	// enable QTR readings
	qtr_init();

	for(uint8_t i = 0; i < QTR_SENS_NUM; i++)
	{
		snprintf(str, sizeof(str), "%s[%.4f]=[%d]\n\r", lf_sens_str[i],
													qtr_get_analog(i),
													qtr_get_digital(i));
		UART_puts(&bluet_uart,str);
	}

	UART_puts(&bluet_uart, "\n\r");

	// stop QTR readings
	qtr_kill();
}
#endif // !_DEBUG_
