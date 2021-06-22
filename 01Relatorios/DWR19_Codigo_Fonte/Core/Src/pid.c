/*
 * pid.c
 *
 * PID algorithm module
 *
 *  Created on: June 5, 2021
 */
#include "pid.h"

/******************************************************************************
PID

@brief	PID Algoritm
@param	PID struct
		inputs to the controller, in1 and in2
@retval none
******************************************************************************/
void pid_calcule(pid_st* pid, float in1, float in2)
{
	// set error
	pid->error = in1 - in2;

	// update sum of errors
	pid->sum_errors_bck = pid->sum_errors;
	pid->sum_errors += pid->prev_error;

	// calculate u
	pid->u_d =  pid->kd_h * (pid->error - pid->prev_error) + A_PID * pid->prev_u_d;
	pid->u = pid->kp_h * pid->error + pid->ki_h * pid->sum_errors + pid->u_d;

	// update previous values
	pid->prev_error = pid->error;
	pid->prev_u_d = pid->u_d;

	// is u above upper saturation?
	if(pid->u > pid->u_sat_a)
	{
		pid->u = pid->u_sat_a;
		//sum of errors frozen
		pid->sum_errors = pid->sum_errors_bck;
	}
	// is u below lower saturation?
	else if	(pid->u < pid->u_sat_b)
	{
		pid->u = pid->u_sat_b;
		//sum of errors frozen
		pid->sum_errors = pid->sum_errors_bck;
	}
}