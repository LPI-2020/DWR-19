/*
 * auxiliares.c
 *
 * Auxiliares module
 *
 *  Created on: June 6, 2021
 */
#include "auxiliares.h"

void sliding_window(uint8_t val, slide_window_t* window)
{
	// refresh count1s
	// subtract window bit 7 to count1s
	window->count1s -= (window->window >> 7);
	// add new value
	window->count1s += val;

	// slide window
	window->window <<=1;
	// put new value at bit 0
	window->window |= val;
}
