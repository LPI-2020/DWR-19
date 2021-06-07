/*
 * move.c
 *
 * Movement control module
 *
 *  Created on: May 5, 2021
 */
#include "move.h"
#include "motor.h"

/******************************************************************************
Private variables
******************************************************************************/
static uint8_t move_flag = 0; // Module flag. Indicates state of motors

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
	// indicate to the module that motors have been enabled
	move_flag = 1;
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
	// indicate to the module that motors have been disable
	move_flag = 0;
}

/******************************************************************************
Move Control

@brief	Controls movement, setting speeds on each motor.
@param	Left and right motor speeds, respectively
@retval none
******************************************************************************/
const static motor_dir_e move_dir[] =
{
		// FORWARD
		MOTOR_FORWARD,
		// BACKWARD
		MOTOR_BACKWARD
};

void move_control(float speedL, float speedR)
{
	if(move_flag == 0)
		// move_start hasn't occurred
		move_start();

	// check if speedL and speedR are positive/negative
	uint8_t dirL = 0.99 + speedL;
	uint8_t dirR = 0.99 - speedR;

	motor_control(&motor_right, speedR * 100, move_dir[dirR & 0x01]);
	motor_control(&motor_left, speedL * 100, move_dir[dirL & 0x01]);
}
