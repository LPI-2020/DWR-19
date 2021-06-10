/*
 * motor.h
 *
 * Motor control module
 *
 *  Created on: May 5, 2021
 */
#ifndef __MOTOR_H__
#define __MOTOR_H__

/******************************************************************************
Define PWM TIM Instance and Channels to be used
******************************************************************************/
#include "tim.h"
#define PWM_TIM_INSTANCE 	(htim3)

// Define Right Motor PWM TIM channel
#define PWM_R_TIM_CHANNEL 	(TIM_CHANNEL_1)

// Define Left Motor PWM TIM channel
#define PWM_L_TIM_CHANNEL 	(TIM_CHANNEL_2)

/******************************************************************************
Motor Struct
******************************************************************************/
typedef struct
{
	const uint8_t pwm_channel;		// Motor pwm channel

	GPIO_TypeDef *GPIO_port_IN1;	// Motor GPIO Port1
	uint16_t GPIO_pin_IN1;			// Motor GPIO Pin1

	GPIO_TypeDef *GPIO_port_IN2;	// Motor GPIO Port2
	uint16_t GPIO_pin_IN2;			// Motor GPIO Pin2
}motor_st;

/******************************************************************************
Motor Directions Enum
******************************************************************************/
typedef enum {
	MOTOR_BACKWARD,
	MOTOR_FORWARD,
	MOTOR_STOP
} motor_dir_e;

/******************************************************************************
Motor Functions
******************************************************************************/
void motor_init(motor_st *m);
void motor_kill(motor_st *m);

void motor_control(motor_st *m,  uint8_t dc, motor_dir_e dir);

/******************************************************************************
Motor Control on each direction
******************************************************************************/
#define motor_stop(_m_) 			motor_control((motor_st *)(_m_), 			   0, MOTOR_STOP)
#define motor_forward(_m_, _dc_) 	motor_control((motor_st *)(_m_), (uint8_t)(_dc_), MOTOR_FORWARD)
#define motor_backward(_m_, _dc_) 	motor_control((motor_st *)(_m_), (uint8_t)(_dc_), MOTOR_BACKWARD)

#endif /* !__MOTOR_H__ */
