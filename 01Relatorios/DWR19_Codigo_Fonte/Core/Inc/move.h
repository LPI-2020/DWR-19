/*
 * move.h
 *
 * Movement control module
 *
 *  Created on: May 5, 2021
 */
#ifndef __MOVE_H__
#define __MOVE_H__

/******************************************************************************
Define Motors peripherals: PWM TIM Instance and Channels to be used
******************************************************************************/
#include "tim.h"

#define PWM_TIM_INSTANCE 	(htim4)

// Define Right Motor PWM TIM channel
#define PWM_R_TIM_CHANNEL 	(TIM_CHANNEL_3)

// Define Left Motor PWM TIM channel
#define PWM_L_TIM_CHANNEL 	(TIM_CHANNEL_4)

/******************************************************************************
Move Enums
******************************************************************************/
typedef enum {
	MOVE_RIGHT = -1,
	MOVE_LEFT = 1
} move_dir_e;

/******************************************************************************
Move Functions
******************************************************************************/
void move_start(void);
void move_stop(void);
void move_control(float speedL, float speedR);

/******************************************************************************
Move in each direction
******************************************************************************/
#define move_forward(_speed_) 		(move_control(_speed_, _speed_))
#define move_backwards(_speed_)		(move_control(-(_speed_), -(_speed_)))
#define move_rotate(_dir_, _speed_) (move_control(-(_dir_) * (_speed_), (_dir_) * (_speed_)))

#endif /*__MOVE_H__ */