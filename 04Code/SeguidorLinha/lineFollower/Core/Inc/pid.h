/*
 * pid.h
 *
 * PID algorithm module
 *
 *  Created on: June 5, 2021
 */
#ifndef __PID_H__
#define __PID_H__

/******************************************************************************
PID constants
******************************************************************************/
#define KP (float) (1)
#define KI (float) (0.1)
#define KD (float) (0.3)

#define a_pid 	(float) (0.3)

// saturation limits
#define U_SAT_A (float) (1.0)	// saturation limit above
#define U_SAT_B (float) (-1.0)	// saturation limit bellow

/******************************************************************************
PID struct
******************************************************************************/
typedef struct
{
	float y;
	float prev_y;
	float kp_h;
	float ki_h;
	float kd_h;
	float error;
	float prev_error;
	float sum_errors;
	float sum_errors_bck;
	float u;
	float u_d;
	float prev_u_d;
} pid_st;

/******************************************************************************
PID calculation
******************************************************************************/
void pid_calcule(pid_st* pid, float ref_sensor, float sensor);

#endif /* __PID_H__ */
