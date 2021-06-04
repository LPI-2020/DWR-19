#ifndef __MOVE_H__
#define __MOVE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "pid.h"
#include "motor.h"

#define PWM_R_TIM_CHANNEL 	(TIM_CHANNEL_1)
#define PWM_L_TIM_CHANNEL 	(TIM_CHANNEL_2)

typedef enum { MOVE_RIGHT, MOVE_LEFT } move_dir;

uint32_t lf_sens[2];

void move_forward();
void move_rotate(move_dir direction);

#ifdef __cplusplus
}
#endif
#endif /*__MOVE_H__ */
