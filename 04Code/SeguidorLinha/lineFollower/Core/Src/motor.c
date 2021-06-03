#include "motor.h"

void motor_stop(motor_st* m)
{
	HAL_GPIO_WritePin(m->GPIO_port_IN1, m->GPIO_pin_IN1, GPIO_PIN_RESET	);
	HAL_GPIO_WritePin(m->GPIO_port_IN2, m->GPIO_pin_IN2, GPIO_PIN_RESET);
}

void motor_forward(motor_st* m)
{
	HAL_GPIO_WritePin(m->GPIO_port_IN1, m->GPIO_pin_IN1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(m->GPIO_port_IN2, m->GPIO_pin_IN2, GPIO_PIN_RESET);
}

void motor_backward(motor_st* m)
{
	HAL_GPIO_WritePin(m->GPIO_port_IN1, m->GPIO_pin_IN1, GPIO_PIN_RESET	);
	HAL_GPIO_WritePin(m->GPIO_port_IN2, m->GPIO_pin_IN2, GPIO_PIN_SET);
}
