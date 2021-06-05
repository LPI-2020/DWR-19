#include "pid.h"

void pid_calcule(pid_st* pid, float ref_sensor, float sensor)
{
	pid->error = ref_sensor - sensor;
	pid->sum_errors_bck = pid->sum_errors;
	pid->sum_errors += pid->prev_error;
	pid->u_d =  pid->kd_h * (pid->y - pid->prev_y) + a_pid * pid->prev_u_d;
	pid->u = pid->kp_h * pid->error + pid->ki_h * pid->sum_errors - pid->u_d;
	pid->prev_error = pid->error;
	pid->prev_y = pid->y;
	pid->prev_u_d = pid->u_d;

	if(pid->u > U_SAT_A)
	{
		pid->u = U_SAT_A;
		pid->sum_errors = pid->sum_errors_bck;
	}
	else if	(pid->u < U_SAT_B)
	{
		pid->u = U_SAT_B;
		pid->sum_errors = pid->sum_errors_bck;
	}
}
