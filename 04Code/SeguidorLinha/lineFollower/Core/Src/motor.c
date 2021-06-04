#include "motor.h"

const GPIO_PinState motor_pin_config[3][2] =
{
		// STOP
		{GPIO_PIN_RESET, GPIO_PIN_RESET},
		// FORWARD
		{GPIO_PIN_SET, GPIO_PIN_RESET},
		// BACKWARD
		{GPIO_PIN_RESET, GPIO_PIN_SET}
};

void motor_control(motor_st *m,  uint8_t dc, motor_dir dir)
{
	HAL_GPIO_WritePin(m->GPIO_port_IN1, m->GPIO_pin_IN1, motor_pin_config[dir][0]);
	HAL_GPIO_WritePin(m->GPIO_port_IN2, m->GPIO_pin_IN2, motor_pin_config[dir][1]);
	set_pwm(&PWM_TIM_INSTANCE, m->pwm_channel, dc);
}
