/*
 * move.c
 *
 * Movement control module
 *
 *  Created on: May 5, 2021
 */
#include "move.h"
#include "motor.h"

#include <math.h> // using fabs()

/******************************************************************************
Private variables
******************************************************************************/
// Module flag. Indicates state of movement
// Equals 1 if its moving, and 0 if its stop
static uint8_t move_flag = 0;

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
void move_control(float speedL, float speedR)
{
	if(move_flag == 0)
		// move_start hasn't occurred
		move_start();

	// speedL and speedR are PWM values, from -1 to +1
	// since dirL and dirR are uint8_t, speed values are truncated
	// so, by adding 0.99 (number less than 1) we get:
	// dirX = 0 if speedX is negative
	// dirX = 1 if speedX is positive
	uint8_t dirL = 0.99 + speedL;
	uint8_t dirR = 0.99 + speedR;

	// dirL and dirR (motor_dir_e) are:
	// 0 -> motor moving BACKWARDS (MOTOR_BACKWARD)
	// 1 -> motor moving FORWARD (MOTOR_FORWARD)
	motor_control(&motor_right, fabs(speedR) * 100, (motor_dir_e)(dirR & 0x01));
	motor_control(&motor_left, fabs(speedL) * 100, (motor_dir_e)(dirL & 0x01));
}
