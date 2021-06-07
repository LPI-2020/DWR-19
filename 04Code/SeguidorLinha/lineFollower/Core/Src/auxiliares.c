#include "auxiliares.h"

#include <stdint.h>

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
