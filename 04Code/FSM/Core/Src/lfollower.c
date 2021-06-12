/*
 * lfollower.c
 *
 * Line Follower Module
 *
 *  Created on: June 5, 2021
 */
#include "lfollower.h"
#include "pid.h"
#include "auxiliares.h"

//#include "stop_sensors.h"

#include <math.h> // using fabs()

/******************************************************************************
Define Debug Symbol
******************************************************************************/
//#define _DEBUG_

#ifdef _DEBUG_
#include "usart.h" // debug
#include <stdio.h>
#endif // !_DEBUG_
/******************************************************************************
Define Move Speeds (from 0 to 1)
******************************************************************************/
#define FORWARD_SPEED 	(float)(0.65)
#define TURN_SPEED 		(float)(0.75)

//#define TIMEOUT_50MS	1

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

// line follower status (enabled 1 or disabled 0)
static uint8_t lfollower_status = 0;

/******************************************************************************
Line Follower Start

@brief	Starts line follower process.
@param	none
@retval	none
******************************************************************************/
void lfollower_start(void)
{
	// start storing QTR Sensor values
	qtr_init();
	// start movement
	move_start();

	// start sampling for PID application
	HAL_TIM_Base_Start_IT(&TIM_LF_PID);
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
	// stop sampling for PID application
	HAL_TIM_Base_Stop_IT(&TIM_LF_PID);

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

void lfollower_isr(void)
{
	// use PID to obtain PWM values to use on motors
	// error = S_LEFT_VAL - S_RIGHT_VAL
	//pid_calcule(&pid, 	DIG_TO_ANALOG(qtr_sens[LF_SENSOR_L]),
	//					DIG_TO_ANALOG(qtr_sens[LF_SENSOR_R]));
	pid_calcule(&pid, qtr_get_analog(LF_SENSOR_L), qtr_get_analog(LF_SENSOR_R));

	// Apply PID to adjust motor PWM/velocity
	move_control(GET_SPEED(-pid.u), GET_SPEED(+pid.u));
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
	// start rotate_timeout
	timeout_start();
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
	//while((GET_SENS_LOGVAL(dir * (QTR_SENS_NUM - 1)) == 0) && (num_timeout_2sec < TIMEOUT_4SEC))
	while((qtr_get_digital(dir * (QTR_SENS_NUM - 1)) == 0) && (num_timeout_2sec < TIMEOUT_4SEC))
		;

	// stop Rotate_Timeout
	timeout_stop();
	// stop rotating
	move_stop();
	// stop storing QTR sensor values
	qtr_kill();

	// if timeout occured, then we must return an error code, signaling a
	// non successful rotate
	if(num_timeout_2sec < TIMEOUT_4SEC)
		return E_LF_TIMEOUT;

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
void lfollower_print_sens(void)
{
	char str[32];

	// enable QTR readings
	qtr_init();

	snprintf(str, sizeof(str), "S1[%f]\n\r", DIG_TO_ANALOG(qtr_sens[SENSOR1]));
	UART_puts(str);

	snprintf(str, sizeof(str), "S3[%f]\n\r", DIG_TO_ANALOG(qtr_sens[SENSOR3]));
	UART_puts(str);

	snprintf(str, sizeof(str), "S4[%f]\n\r", DIG_TO_ANALOG(qtr_sens[SENSOR4]));
	UART_puts(str);

	snprintf(str, sizeof(str), "S5[%f]\n\r", DIG_TO_ANALOG(qtr_sens[SENSOR5]));
	UART_puts(str);

	snprintf(str, sizeof(str), "S6[%f]\n\r", DIG_TO_ANALOG(qtr_sens[SENSOR6]));
	UART_puts(str);

	snprintf(str, sizeof(str), "S8[%f]\n\r\n\r", DIG_TO_ANALOG(qtr_sens[SENSOR8]));
	UART_puts(str);

	// stop QTR readings
	qtr_kill();
}
#endif // !_DEBUG_
