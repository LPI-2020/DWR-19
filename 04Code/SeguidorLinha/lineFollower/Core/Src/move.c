#include "move.h"
#include "usart.h"
#include "stdio.h"

#define PWM_TIM_INSTANCE 	(htim3)
#define PWM_R_TIM_CHANNEL 	(TIM_CHANNEL_1)
#define PWM_L_TIM_CHANNEL 	(TIM_CHANNEL_2)

#define FORWARD_SPEED (float) 0.78
#define TURN_SPEED (float) 0.7

static void set_forward();
static void set_left();
static void set_right();
static void set_backward();

void (*func_set_ptr[])(void) = {	set_right, set_left		};

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

static void set_forward()
{
	motor_forward(&motor_right);
	motor_forward(&motor_left);
}

static void set_left()
{
	motor_forward(&motor_right);
	motor_stop(&motor_left);
}

static void set_right()
{
	motor_stop(&motor_right);
	motor_forward(&motor_left);
}

static void set_backward()
{
	motor_backward(&motor_right);
	motor_backward(&motor_left);
}

void line_follower()
{
	set_forward();
	pid_calcule(&pid, (qtr[SENSOR3]* 3.3 / 4095), (qtr[SENSOR6] * 3.3 / 4095));
	set_pwm(&PWM_TIM_INSTANCE, PWM_L_TIM_CHANNEL, (FORWARD_SPEED + pid.u * (1 - FORWARD_SPEED)) * 100);
	set_pwm(&PWM_TIM_INSTANCE, PWM_R_TIM_CHANNEL, (FORWARD_SPEED - pid.u * (1 - FORWARD_SPEED)) * 100);
}


void turn(direction_e direction)
{
	func_set_ptr[direction & 0x01]();
	set_pwm(&PWM_TIM_INSTANCE, PWM_R_TIM_CHANNEL, TURN_SPEED * 100 * (direction & 0x01));
	set_pwm(&PWM_TIM_INSTANCE, PWM_L_TIM_CHANNEL, TURN_SPEED * 100 * (1 - (direction & 0x01)));
}
