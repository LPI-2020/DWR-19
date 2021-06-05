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

#include <stdint.h> // using uint32_t

/******************************************************************************
Move Directions Enum
******************************************************************************/
typedef enum { MOVE_RIGHT, MOVE_LEFT } move_dir_e;

/******************************************************************************
Line Follower Sensor
******************************************************************************/
extern uint32_t lf_sens[2];

/******************************************************************************
Move Functions
******************************************************************************/
void move_start(void);
void move_stop(void);

void move_forward(void);
void move_rotate(move_dir_e direction);

//#ifdef __cplusplus
//}
//#endif
#endif /*__MOVE_H__ */
