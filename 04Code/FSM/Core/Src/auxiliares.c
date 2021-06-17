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

/******************************************************************************
Mean of a sliding Window

@brief	Executes a sliding window, inserting a new value on the first position
		of the window. Returns mean of window.
@param	New value
		Window
		Window size
@retval mean of window
******************************************************************************/
float mean_window(float val, float* window, uint8_t w_size)
{
	float sum = 0;

	for(uint8_t i = (w_size - 1); i > 0; i--)
	{
		window[i] = window[i - 1];
		sum += window[i];
	}

	window[0] = val;
	sum += val;

	return (sum / w_size);
}
