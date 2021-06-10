/*
 * auxiliares.c
 *
 * Auxiliares module
 *
 *  Created on: June 6, 2021
 */
#include "auxiliares.h"

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
