#ifndef __MOVE_H__
#define __MOVE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "qtr.h"
#include "pid.h"
#include "motor.h"

typedef enum { RIGHT, LEFT } direction_e;

#define MOVE_RIGHT 	0
#define MOVE_LEFT	1

void line_follower();
void turn(uint8_t direction);

#ifdef __cplusplus
}
#endif
#endif /*__MOVE_H__ */
