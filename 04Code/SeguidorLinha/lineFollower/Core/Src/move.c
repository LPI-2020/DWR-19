/*
 * move.c
 *
 * Movement control module
 *
 *  Created on: May 5, 2021
 */
#include "move.h"
#include "pid.h"
#include "motor.h"

/******************************************************************************
Define Move Speeds (from 0 to 1)
******************************************************************************/
//#define FORWARD_SPEED 	(float)(0.78)
//#define TURN_SPEED 		(float)(0.7)

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
	.GPIO_pin_IN2 	= IN2_LEFT_Pin
};

// List of motors
static motor_st* motors[] = { &motor_right, &motor_left };

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

@brief	Set both motors to FORWARD at speed = speed
@param	speed value, from 0 to 1
@retval none
******************************************************************************/
//void move_forward(float speed)
//{
//	// Set both motors to Forward
//	motor_forward(&motor_right, speed);
//	motor_forward(&motor_left, 	speed);
//}

/******************************************************************************
Move Rotate

@brief	Set motor to FORWARD, in the opposite position to the one in which it
		will turn.
		i.e: 	Rotate right: set motor LEFT to FORWARD and STOP motor RIGHT
				Rotate left: set motor RIGHT to FORWARD and STOP motor LEFT
@param	none
@retval none
******************************************************************************/
//void move_rotate(move_dir_e direction)
//{
//	// Set motor to forward with speed TURN_SPEED
////	motor_forward(motors[1 - (direction & 0x01)], TURN_SPEED * 100);
//	// Stop other motor
//	motor_stop(motors[direction & 0x01]);
//}

//void move(float speedL, float speedR)
//{
//	motor_forward(&motor_right, speedR);
//	motor_forward(&motor_left, speedL);
//}

const static motor_dir_e move_dir[] =
{
		// FORWARD
		MOTOR_FORWARD,
		// BACKWARD
		MOTOR_BACKWARD
};

void move(float speedL, float speedR)
{
	uint8_t dirL = 0.99 + speedL;
	uint8_t dirR = 0.99 - speedR;

	motor_control(&motor_right, speedR, move_dir[dirR & 0x01]);
	motor_control(&motor_left, speedL, move_dir[dirL & 0x01]);
}
