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

#include "stop_sensors.h"

#include <math.h> // using fabs()

/******************************************************************************
Define Move Speeds (from 0 to 1)
******************************************************************************/
#define FORWARD_SPEED 	(float)(0.65)
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
#define _CALC_SPEED1_
/*****************************************************************************/

// calculate speed no.1
#ifdef _CALC_SPEED1_

	#define GET_SPEED(_u_) (FORWARD_SPEED + (_u_) * (1 - FORWARD_SPEED))

#endif // !_CALC_SPEED1_
// calculate speed no.2 - with extra speed on the straights
#ifdef _CALC_SPEED2_

	#define GET_SPEED(_u_, _extra_) (FORWARD_SPEED * (1 - (_extra_)) +			\
									(_u_)*(1 - FORWARD_SPEED*(1 - (_extra_))))

#endif // !_CALC_SPEED2_
// calculate speed no.3 - with extra speed on the straights
#ifdef _CALC_SPEED3_

	#define GET_SPEED_P(_u_, _extra_) (FORWARD_SPEED + (1 - FORWARD_SPEED) * 	\
									(1 - fabs(_extra_)) + (1 - FORWARD_SPEED -	\
									(1 - FORWARD_SPEED)*(1 - fabs(_extra_)))*	\
									(_u_))

#endif // !_CALC_SPEED3_

/******************************************************************************
Define Line Follower Sensors in use
******************************************************************************/
// Number of sensors in use
#define LF_SENS_NUM (4)
static uint32_t lf_sens[LF_SENS_NUM];

#define ST_SENS_NUM	(2)
static uint32_t st_sens[ST_SENS_NUM];

// Sensor elements
typedef enum {
	SENSOR3,	// Line Follower RIGHT Sensor
	SENSOR4,	// Rotate RIGHT Sensor
	SENSOR5,	// Rotate LEFT Sensor
	SENSOR6		// Line Follower LEFT Sensor
} sensor_e;

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

//static pid_st pid = {
//	.y 			= 0,	// <----
//	.prev_y 	= 0, 	// <------
//	.kp_h 		= KP,
//	.ki_h 		= KI * TIMER6_PERIOD,
//	.kd_h 		= KD * (1 - A_PID) / TIMER6_PERIOD,
//	.error 		= 0,
//	.sum_errors = 0,
//	.prev_error = 0,
//	.u 			= 0,
//	.u_d 		= 0,
//	.prev_u_d 	= 0
//};

// Define array of LAST_ERRORS_SIZE elements, of pid->error
#define LAST_ERRORS_SIZE (8)
static float last_errors[LAST_ERRORS_SIZE] = {0};

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
	// error = S_LEFT_VAL - S_RIGHT_VAL
	pid_calcule(&pid, 	DIG_TO_ANALOG(lf_sens[SENSOR6]),
						DIG_TO_ANALOG(lf_sens[SENSOR3]));

#ifdef _DEBUG_
	sprintf(Tx_buffer, "left %f   right %f\r\n", GET_SPEED(-pid.u), GET_SPEED(+pid.u));
	sprintf(Tx_buffer, "sensor left %f\r\nsensor right %f\r\n",
							DIG_TO_ANALOG(lf_sens[SENSOR6]),
							DIG_TO_ANALOG(lf_sens[SENSOR3]));
	transmit_string(Tx_buffer);
#endif // !_DEBUG_

	// according to calculated error = S_LEFT_VAL - S_RIGHT_VAL:
	// command var. LEFT is equal to (+pid.u)
	// command var. RIGHT is equal to (-pid.u)
#ifdef _CALC_SPEED1_
	move_control(GET_SPEED(-pid.u), GET_SPEED(+pid.u));
#endif // !_CALC_SPEED1_
#ifdef _CALC_SPEED2_
	static float mean_err;

	// calculates mean of the last PID errors
	mean_err = mean_window(pid.error, last_errors, LAST_ERRORS_SIZE);
	move_control(GET_SPEED_P(-pid.u, mean_err), GET_SPEED_P(+pid.u, mean_err));
#endif // !_CALC_SPEED2_
}

/******************************************************************************
Line Follower Stop

@brief 	Stops line follower process.
@param	none
@retval	none
******************************************************************************/

uint8_t lfollower_rotate(move_dir_e dir)
{
	// start movement and rotate to 'dir' at speed equal to TURN_SPEED
	move_rotate(dir, TURN_SPEED);

	// start storing
	HAL_ADC_Start_DMA(&OBS_DETECTOR_ADC, st_sens, ST_SENS_NUM);

	// if dir == MOVE_RIGHT, check when SENSOR1 is over the line
	// if dir == MOVE_LEFT, check when SENSOR8 is over the line

	// dir can be -1 (MOVE_RIGHT) or +1 (MOVE_LEFT)
	dir += 1;
	// dir is now 0 or 2
	dir >>= 1;
	// dir is now 0 (MOVE_RIGHT) or 1 (MOVE_LEFT)

	// reset number of 2second Timeouts
	num_timeout_2sec = 0;
	// start Rotate_Timeout
	HAL_TIM_Base_Start_IT(&TIM_LF_ROTATE);

	// while Sensor is not over the line and timeout has not occurred
	while((DIG_TO_ANALOG(st_sens[1 + (dir & 0x01)]) < (2.0)) && (num_timeout_2sec < TIMEOUT_4SEC))
		;

	// stop rotating
	move_stop();

	// stop Rotate_Timeout
	HAL_TIM_Base_Stop_IT(&TIM_LF_ROTATE);

	// if timeout didnt occurred then rotate was completed -> Return 0
	// if timeout occured, then we must return an error code, signaling a
	// non successfull rotate -> return 1
	return !(num_timeout_2sec < TIMEOUT_4SEC);
}

/******************************************************************************
Line Follower Start

@brief	Starts line follower process.
@param	none
@retval	none
******************************************************************************/
void lfollower_start(void)
{
	// start storing Line Follower Sensor values
	HAL_ADC_Start_DMA(&ADC_LF_SENS_DMA, lf_sens, LF_SENS_NUM);
	// start sampling for PID application
	HAL_TIM_Base_Start_IT(&TIM_LF_SENS_PID);
	// start movement
	move_start();
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
	HAL_ADC_Stop_DMA(&ADC_LF_SENS_DMA);
	// stop sampling for PID application
	HAL_TIM_Base_Stop_IT(&TIM_LF_SENS_PID);
	// stop movement
	move_stop();
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
	sprintf(Tx_buffer, "Sensor 1: %ld\r\n", st_sens[0]);
	transmit_string(Tx_buffer);
	HAL_Delay(100);

	sprintf(Tx_buffer, "Sensor 3: %ld\r\n", lf_sens[0]);
	transmit_string(Tx_buffer);
	HAL_Delay(100);

	sprintf(Tx_buffer, "Sensor 4: %ld\r\n", lf_sens[1]);
	transmit_string(Tx_buffer);
	HAL_Delay(100);

	sprintf(Tx_buffer, "Sensor 5: %ld\r\n", lf_sens[2]);
	transmit_string(Tx_buffer);
	HAL_Delay(100);

	sprintf(Tx_buffer, "Sensor 6: %ld\r\n", lf_sens[3]);
	transmit_string(Tx_buffer);
	HAL_Delay(100);

	sprintf(Tx_buffer, "Sensor 8: %ld\r\n", st_sens[1]);
	transmit_string(Tx_buffer);
	HAL_Delay(100);
	HAL_Delay(1000);
}
#endif // !_DEBUG_
