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

//void move_forward(float speed);
//void move_rotate(move_dir_e direction);

void move(float speedL, float speedR);

/******************************************************************************
Move in each direction
******************************************************************************/
#define move_rotate(_dir_, _speed_) (move((1 - (_dir_))*(_speed_), (_dir_)*(_speed_)))
#define move_forward(_speed_) 		(move(_speed_, _speed_))
#define move_backward(_speed_)		(move(_speed_, _speed_))

#endif /*__MOVE_H__ */
