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
Move Directions Enum
******************************************************************************/
typedef enum { MOVE_RIGHT, MOVE_LEFT } move_dir_e;

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
#define move_backwards(_speed_)		(move_control(-(_speed_), -_speed_))
#define move_rotate(_dir_, _speed_) (move_control((1 - ((move_dir_e)_dir_))*(_speed_), \
													((move_dir_e)_dir_)*(_speed_)))

#endif /*__MOVE_H__ */
