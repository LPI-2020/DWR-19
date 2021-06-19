/*
 * auxiliares.h
 *
 * Auxiliares module
 *
 *  Created on: June 6, 2021
 */
#ifndef __AUXILIARES_H__
#define __AUXILIARES_H__

#include <stdint.h> // using uint8_t

/******************************************************************************
Sliding Window
******************************************************************************/
typedef struct
{
	uint8_t window;			// sliding window
	uint8_t count1s;		// count 1s in window
} slide_window_t;

void sliding_window(uint8_t val, slide_window_t* window);

/******************************************************************************
Obstacle Detector Peripherals
******************************************************************************/
// Convert digital value to analog
#define DIG_TO_ANALOG(_val_)	((_val_) * 3.3 / 4095)

#endif /* __AUXILIARES_H__ */
