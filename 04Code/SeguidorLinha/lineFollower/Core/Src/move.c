#include "move.h"
#include "usart.h"
#include "stdio.h"

#define FORWARD_SPEED (float) 0.78
#define TURN_SPEED (float) 0.7

typedef enum { SENSOR_RIGHT, SENSOR_LEFT } sensor_e;

static motor_st motor_right = {
	.pwm_channel = PWM_R_TIM_CHANNEL,
	.GPIO_port_IN1 = IN1_RIGHT_GPIO_Port,
	.GPIO_pin_IN1 = IN1_RIGHT_Pin,
	.GPIO_port_IN2 = IN2_RIGHT_GPIO_Port,
	.GPIO_pin_IN2 = IN2_RIGHT_Pin

};

static motor_st motor_left = {
	.pwm_channel = PWM_L_TIM_CHANNEL,
	.GPIO_port_IN1 = IN1_LEFT_GPIO_Port,
	.GPIO_pin_IN1 = IN1_LEFT_Pin,
	.GPIO_port_IN2 = IN2_LEFT_GPIO_Port,
	.GPIO_pin_IN2 =  IN2_LEFT_Pin
};

static motor_st* motors[] = { &motor_right, &motor_left	};

static pid_st pid = {
		.y = 0,			// <----
		.prev_y = 0, 	// <------
		.kp_h = KP,
		.ki_h = KI * TIMER6_PERIOD,
		.kd_h = KD * (1 - a_pid) / TIMER6_PERIOD,
		.error = 0,
		.sum_errors = 0,
		.prev_error = 0,
		.u = 0,
		.u_d = 0,
		.prev_u_d = 0
};


void move_forward()
{
	pid_calcule(&pid, (lf_sens[SENSOR_RIGHT] * 3.3 / 4095), (lf_sens[SENSOR_LEFT] * 3.3 / 4095));
	motor_forward(&motor_right, (FORWARD_SPEED - pid.u * (1 - FORWARD_SPEED)) * 100);
	motor_forward(&motor_left, (FORWARD_SPEED + pid.u * (1 - FORWARD_SPEED)) * 100);
	//set_pwm(&PWM_TIM_INSTANCE, PWM_L_TIM_CHANNEL, );
	//set_pwm(&PWM_TIM_INSTANCE, PWM_R_TIM_CHANNEL, );

}


void move_rotate(move_dir direction)
{
	//set_pwm(&PWM_TIM_INSTANCE, PWM_R_TIM_CHANNEL, TURN_SPEED * 100 * (direction & 0x01));
	//set_pwm(&PWM_TIM_INSTANCE, PWM_L_TIM_CHANNEL, TURN_SPEED * 100 * (1 - (direction & 0x01)));
	motor_forward(motors[1 - (direction & 0x01)], TURN_SPEED * 100);
	motor_stop(motors[direction & 0x01]);
}
