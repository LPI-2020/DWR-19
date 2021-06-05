/*
 * move.c
 *
 *  Created on: May 5, 2021
 */
#include "move.h"
#include "pid.h"
#include "motor.h"
/******************************************************************************
Define Move Speeds
******************************************************************************/
#define FORWARD_SPEED 	(float)(0.78)
#define TURN_SPEED 		(float)(0.7)

/******************************************************************************
Define Sensors in use
******************************************************************************/
// Line Follower Sensor
uint32_t lf_sens[2];

// Sensor elements
typedef enum { SENSOR_RIGHT, SENSOR_LEFT } sensor_e;
/******************************************************************************
Define Motors in use
******************************************************************************/
// Right Motor Struct
static motor_st motor_right = {
	.pwm_channel 	= PWM_R_TIM_CHANNEL,

	.GPIO_port_IN1 	= IN1_RIGHT_GPIO_Port,
	.GPIO_pin_IN1 	= IN1_RIGHT_Pin,

	.GPIO_port_IN2 	= IN2_RIGHT_GPIO_Port,
	.GPIO_pin_IN2 	= IN2_RIGHT_Pin
};
// Left Motor Struct
static motor_st motor_left = {
	.pwm_channel 	= PWM_L_TIM_CHANNEL,

	.GPIO_port_IN1 	= IN1_LEFT_GPIO_Port,
	.GPIO_pin_IN1 	= IN1_LEFT_Pin,

	.GPIO_port_IN2 	= IN2_LEFT_GPIO_Port,
	.GPIO_pin_IN2 	=  IN2_LEFT_Pin
};

// List of motors
static motor_st* motors[] = { &motor_right, &motor_left };

/******************************************************************************
Define PID algorithm to be used
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
Move Start

@brief	Start movement. Enables both motors
@param	none
@retval none
******************************************************************************/
void move_start(void)
{
	motor_init(&motor_right);
	motor_init(&motor_left);
}

/******************************************************************************
Move Stop

@brief	Stop movement. Disables both motors
@param	none
@retval none
******************************************************************************/
void move_stop(void)
{
	motor_kill(&motor_right);
	motor_kill(&motor_left);
}

/******************************************************************************
Move Forward

@brief	Set both motors to FORWARD with base speed equal to FORWARD_SPEED (%)
		>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> explain (FORWARD_SPEED - pid.u * (1 - FORWARD_SPEED))!!!
@param	none
@retval none
******************************************************************************/
void move_forward(void)
{
	// Apply PID to adjust motor PWM/velocity
	pid_calcule(&pid, (lf_sens[SENSOR_RIGHT] * 3.3 / 4095), (lf_sens[SENSOR_LEFT] * 3.3 / 4095));

	// Set both motors to Forward
	motor_forward(&motor_right, (FORWARD_SPEED - pid.u * (1 - FORWARD_SPEED)) * 100);
	motor_forward(&motor_left, 	(FORWARD_SPEED + pid.u * (1 - FORWARD_SPEED)) * 100);
}

/******************************************************************************
Move Rotate

@brief	Set motor to FORWARD, in the opposite position to the one in which it
		will turn.
		i.e: 	Rotate right: set motor LEFT to FORWARD and STOP motor RIGHT
				Rotate left: set motor RIGHT to FORWARD and STOP motor LEFT
@param	none
@retval none
******************************************************************************/
void move_rotate(move_dir_e direction)
{
	// Set motor to forward with speed TURN_SPEED (%)
	motor_forward(motors[1 - (direction & 0x01)], TURN_SPEED * 100);
	motor_stop(motors[direction & 0x01]);
}
