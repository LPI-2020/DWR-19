/*
 * motor.c
 *
 * Motor control module
 *
 *  Created on: May 5, 2021
 */
#include "motor.h"

/******************************************************************************
Motor Init

@brief	Start PWM generation to a given motor
@param	Motor to be initialized
@retval none
******************************************************************************/
void motor_init(motor_st *m)
{
	HAL_TIM_PWM_Start(&PWM_TIM_INSTANCE, m->pwm_channel);
}

/******************************************************************************
Motor Kill

@brief	Stops PWM generation to a given motor
@param	Motor to be killed
@retval none
******************************************************************************/
void motor_kill(motor_st *m)
{
	HAL_TIM_PWM_Stop(&PWM_TIM_INSTANCE, m->pwm_channel);
}

/******************************************************************************
Define motor GPIO Pins config according to each direction
******************************************************************************/
static const GPIO_PinState motor_pin_config[3][2] =
{
		// Motor BACKWARD
		{GPIO_PIN_RESET, GPIO_PIN_SET},
		// Motor FORWARD
		{GPIO_PIN_SET, GPIO_PIN_RESET},
		// Motor STOP
		{GPIO_PIN_RESET, GPIO_PIN_RESET}
};

/******************************************************************************
Motor control

@brief	Controls Motor PWM duty cycle in desired direction
@param	Motor to be controlled
		New PWM duty cycle
		Direction of motor rotation
@retval none
******************************************************************************/
void motor_control(motor_st *m,  uint8_t dc, motor_dir_e dir)
{
	// Write motor GPIO Pin1
	HAL_GPIO_WritePin(m->GPIO_port_IN1, m->GPIO_pin_IN1, motor_pin_config[dir][0]);
	// Write motor GPIO Pin1
	HAL_GPIO_WritePin(m->GPIO_port_IN2, m->GPIO_pin_IN2, motor_pin_config[dir][1]);
	// Set/Update motor PWM duty cycle
	set_pwm(&PWM_TIM_INSTANCE, m->pwm_channel, dc);
}
