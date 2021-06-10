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

// Convert digital value to analog
#define DIG_TO_ANALOG(_val_)	((_val_) * 3.3 / 4095)

// Mean of a sliding Window
float mean_window(float val, float* window, uint8_t w_size);

#endif /* __AUXILIARES_H__ */
