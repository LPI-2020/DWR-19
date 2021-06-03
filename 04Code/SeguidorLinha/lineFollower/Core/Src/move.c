#include "move.h"

#define PWM_TIM_INSTANCE 	(htim3)
#define PWM_R_TIM_CHANNEL 	(TIM_CHANNEL_1)
#define PWM_L_TIM_CHANNEL 	(TIM_CHANNEL_2)

static void move_front();

static pid_st pid_right = {
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

static pid_st pid_left = {
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

static motor_st motor_right = {
	.GPIO_port_IN1 = IN1_RIGHT_GPIO_Port,
	.GPIO_pin_IN1 = IN1_RIGHT_Pin,
	.GPIO_port_IN2 = IN2_RIGHT_GPIO_Port,
	.GPIO_pin_IN2 = IN2_RIGHT_Pin
};

static motor_st motor_left = {
	.GPIO_port_IN1 = IN1_LEFT_GPIO_Port,
	.GPIO_pin_IN1 = IN1_LEFT_Pin,
	.GPIO_port_IN2 = IN2_LEFT_GPIO_Port,
	.GPIO_pin_IN2 =  IN2_LEFT_Pin
};

void move_front()
{
	motor_front(&motor_right);
	motor_front(&motor_left);
}

void line_follower()
{
	move_front();
	pid_calcule(&pid_right, qtr[SENSOR3], qtr[SENSOR6]);
	pid_calcule(&pid_left, qtr[SENSOR6], qtr[SENSOR3]);
	set_pwm(&PWM_TIM_INSTANCE, PWM_R_TIM_CHANNEL, pid_right.u * 100);
	set_pwm(&PWM_TIM_INSTANCE, PWM_L_TIM_CHANNEL, pid_left.u * 100);

}