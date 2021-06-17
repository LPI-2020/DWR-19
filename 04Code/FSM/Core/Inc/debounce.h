/*
 * debounce.h
 *
 * Debounce Module
 *
 *  Created on: June 14, 2021
 */
#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include "auxiliares.h" // using slide_window_t
#include <stdint.h>		// using uint16_t

/******************************************************************************
Debounce Peripherals
******************************************************************************/
#include "tim.h"
#define TIM_DEBOUNCE		(htim13)

/******************************************************************************
Debounce Struct
******************************************************************************/
#include "gpio.h"

typedef struct
{
	slide_window_t sw;

	GPIO_TypeDef* GPIOx;	// GPIO button port
	uint16_t GPIO_Pin;		// GPIO button pin

	uint8_t pin_output;		// button output
} debounce_t;

extern debounce_t button;
/******************************************************************************
Debounce Functions
******************************************************************************/
// start/stop debounce
void debounce_start(debounce_t *s, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void debounce_stop(void);
void debounce_isr(void);

#endif /* __DEBOUNCE_H__ */
