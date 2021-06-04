#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"

#define PWM_TIM_INSTANCE 	(htim3)

typedef struct
{
	const uint8_t pwm_channel;
	GPIO_TypeDef *GPIO_port_IN1;
	uint16_t GPIO_pin_IN1;
	GPIO_TypeDef *GPIO_port_IN2;
	uint16_t GPIO_pin_IN2;
}motor_st;

typedef enum { MOTOR_STOP, MOTOR_FORWARD, MOTOR_BACKWARD} motor_dir;

void motor_control(motor_st *m,  uint8_t dc, motor_dir dir);

#define motor_stop(_m_) 			motor_control((motor_st *)(_m_), (uint8_t)0, MOTOR_STOP)
#define motor_forward(_m_, _dc_) 	motor_control((motor_st *)(_m_), (uint8_t)(_dc_), MOTOR_FORWARD)
#define motor_backward(_m_, _dc_) 	motor_control((motor_st *)(_m_), (uint8_t)(_dc_), MOTOR_BACKWARD)

#ifdef __cplusplus
}
#endif
#endif /*__MOTOR_H__ */
