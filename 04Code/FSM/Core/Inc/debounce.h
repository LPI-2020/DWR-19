/*
 * debounce.h
 *
 * Debounce Module
 *
 *  Created on: June 14, 2021
 */
#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include "stm32f7xx_hal.h"
#include "auxiliares.h" // using slide_window_t

/******************************************************************************
Debounce Peripherals
******************************************************************************/
#include "tim.h"
// Debounce Timer
#define TIM_DEBOUNCE		(htim7)

/******************************************************************************
Debounce Struct
******************************************************************************/
typedef struct
{
	slide_window_t sw;		// Debounce Sliding Window

	GPIO_TypeDef* GPIOx;	// GPIO button port
	uint16_t GPIO_Pin;		// GPIO button pin

	uint8_t pin_output;		// Button output
} debounce_t;

extern debounce_t button; // define this in your code

/******************************************************************************
Debounce Functions
******************************************************************************/
void debounce_start(debounce_t *s, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void debounce_stop(void);
void debounce_isr(void);

#endif /* __DEBOUNCE_H__ */
