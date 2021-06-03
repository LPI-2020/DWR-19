#ifndef __MOTOR_H__
#define __MOTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

typedef struct
{
	GPIO_TypeDef *GPIO_port_IN1;
	uint16_t GPIO_pin_IN1;
	GPIO_TypeDef *GPIO_port_IN2;
	uint16_t GPIO_pin_IN2;
}motor_st;

void motor_front(motor_st* m);

#ifdef __cplusplus
}
#endif
#endif /*__MOTOR_H__ */