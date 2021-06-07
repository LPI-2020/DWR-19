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
@param
@retval none
******************************************************************************/
//void pid_calcule(pid_st* pid, float ref_sensor, float sensor)
//{
//	// set error
//	pid->error = ref_sensor - sensor;
//
//	// update sum of errors
//	pid->sum_errors_bck = pid->sum_errors;
//	pid->sum_errors += pid->prev_error;
//
//	// calculate u
//	pid->u_d =  pid->kd_h * (pid->y - pid->prev_y) + a_pid * pid->prev_u_d;
//	pid->u = pid->kp_h * pid->error + pid->ki_h * pid->sum_errors - pid->u_d;
//
//	// update previous values
//	pid->prev_error = pid->error;
//	pid->prev_y = pid->y;
//	pid->prev_u_d = pid->u_d;
//
//	// is u above upper saturation?
//	if(pid->u > U_SAT_A)
//	{
//		pid->u = U_SAT_A;
//		//sum of errors frozen
//		pid->sum_errors = pid->sum_errors_bck;
//	}
//	// is u below lower saturation?
//	else if	(pid->u < U_SAT_B)
//	{
//		pid->u = U_SAT_B;
//		//sum of errors frozen
//		pid->sum_errors = pid->sum_errors_bck;
//	}
//}

void pid_calcule(pid_st* pid, float l_sensor, float r_sensor)
{
	// set error
	pid->error = l_sensor - r_sensor;

	// update sum of errors
	pid->sum_errors_bck = pid->sum_errors;
	pid->sum_errors += pid->prev_error;

	// calculate u
	pid->u_d =  pid->kd_h * (pid->error - pid->prev_error) + a_pid * pid->prev_u_d;
	pid->u = pid->kp_h * pid->error + pid->ki_h * pid->sum_errors + pid->u_d;

	// update previous values
	pid->prev_error = pid->error;
	pid->prev_u_d = pid->u_d;

	// is u above upper saturation?
	if(pid->u > U_SAT_A)
	{
		pid->u = U_SAT_A;
		//sum of errors frozen
		pid->sum_errors = pid->sum_errors_bck;
	}
	// is u below lower saturation?
	else if	(pid->u < U_SAT_B)
	{
		pid->u = U_SAT_B;
		//sum of errors frozen
		pid->sum_errors = pid->sum_errors_bck;
	}
}
