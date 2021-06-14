/*
 * route.h
 *
 *  Created on: 14/06/2021
 */

#ifndef __ROUTE_H__
#define __ROUTE_H__

#include "stdint.h"

#define CROSS_NUM 	(10)
#define ROOM_NUM	(8)

typedef struct{
	uint8_t rooms[CROSS_NUM][ROOM_NUM];
	uint8_t crosses[CROSS_NUM][4];
} route_t;



#endif /* _ROUTE_H_ */
