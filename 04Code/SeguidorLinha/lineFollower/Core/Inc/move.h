/*
 * move.h
 *
 *  Created on: May 5, 2021
 */
#ifndef __MOVE_H__
#define __MOVE_H__

//#ifdef __cplusplus
//extern "C" {
//#endif
//
///* Includes ------------------------------------------------------------------*/
//#include "main.h"
//#include "tim.h"
//#include "pid.h"
//#include "motor.h"

/******************************************************************************
Define PWM TIM channels to be used
******************************************************************************/
#include "tim.h"
#define PWM_R_TIM_CHANNEL 	(TIM_CHANNEL_1)
#define PWM_L_TIM_CHANNEL 	(TIM_CHANNEL_2)

/******************************************************************************
Move Directions Enum
******************************************************************************/
typedef enum { MOVE_RIGHT, MOVE_LEFT } move_dir_e;

/******************************************************************************

******************************************************************************/
extern uint32_t lf_sens[2];

/******************************************************************************
Move Functions
******************************************************************************/
void move_forward(void);
void move_rotate(move_dir_e direction);

//#ifdef __cplusplus
//}
//#endif
#endif /*__MOVE_H__ */
