#ifndef __PID_H__
#define __PID_H__

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#include "stm32f7xx_hal.h"

#define KP (float) (1)
#define KI (float) (0.1)
#define KD (float) (0.3)

#define a_pid 	(float) (0.3)

#define U_SAT_A (float) (1.0)
#define U_SAT_B (float) (-1.0)

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

void pid_calcule(pid_st* pid, float ref_sensor, float sensor);

//#ifdef __cplusplus
//}
//#endif

#endif /* __PID_H__ */
