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
#define A_PID (float) (0.3)

#define U_SAT_A (1)
#define U_SAT_B (-1)
/******************************************************************************
PID struct
******************************************************************************/
typedef struct
{
	float kp_h;				// PROPORTIONAL constant with h (sampling time)
	float ki_h;				// INTEGRAL constant with h
	float kd_h;				// DERIVATIVE constant with h

	float error;			// current error
	float prev_error;		// previous error
	float sum_errors;		// sum of previous errors
	float sum_errors_bck;	// backup of sum of previous errors

	float u_d;				// derivative component value
	float prev_u_d;			// previous derivative component value

	float u;				// command variable
	float u_sat_a;			// command variable saturation limit ABOVE
	float u_sat_b;			// command variable saturation limit BELLOW
} pid_st;

/******************************************************************************
PID calculation
******************************************************************************/
void pid_calcule(pid_st* pid, float in1, float in2);

#endif /* __PID_H__ */
