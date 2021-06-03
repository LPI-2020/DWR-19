#include "pid.h"

//void pid_init(pid_st* pid, float sample_time)
//{
//	pid->y = 0;		// <----
//	pid->prev_y = 0; 	// <------
//	pid->kp_h = KP;
//	pid->ki_h = KI * sample_time;
//	pid->kd_h = KD * (1 - a_pid) / sample_time;
//	pid->error = 0;
//	pid->sum_errors = 0;
//	pid->prev_error = 0;
//	pid->u = 0;
//	pid->u_d = 0;
//	pid->prev_u_d = 0;
//}

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