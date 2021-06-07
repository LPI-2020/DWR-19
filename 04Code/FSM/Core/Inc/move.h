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

void move_forward(float speed);
void move_rotate(move_dir_e direction);

#endif /*__MOVE_H__ */