/*
 * motor.h
 *
 *  Created on: May 5, 2021
 */
#ifndef __MOTOR_H__
#define __MOTOR_H__

//#ifdef __cplusplus
//extern "C" {
//#endif

///* Includes ------------------------------------------------------------------*/
//#include "main.h"

/******************************************************************************
Define PWM TIM Instance to be used
******************************************************************************/
#include "tim.h"
#define PWM_TIM_INSTANCE 	(htim3)

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
typedef enum { MOTOR_STOP, MOTOR_FORWARD, MOTOR_BACKWARD} motor_dir_e;

/******************************************************************************
Motor Control
******************************************************************************/
void motor_control(motor_st *m,  uint8_t dc, motor_dir_e dir);

/******************************************************************************
Motor Control on each direction
******************************************************************************/
#define motor_stop(_m_) 			motor_control((motor_st *)(_m_), 			   0, MOTOR_STOP)
#define motor_forward(_m_, _dc_) 	motor_control((motor_st *)(_m_), (uint8_t)(_dc_), MOTOR_FORWARD)
#define motor_backward(_m_, _dc_) 	motor_control((motor_st *)(_m_), (uint8_t)(_dc_), MOTOR_BACKWARD)

//#ifdef __cplusplus
//}
//#endif
#endif /* !__MOTOR_H__ */
