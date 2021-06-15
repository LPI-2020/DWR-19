/*
 * debounce.h
 *
 * Debounce Module
 *
 *  Created on: June 14, 2021
 */
#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#include <stdint.h>
#include "gpio.h"

/******************************************************************************
Debounce Peripherals
******************************************************************************/
#include "tim.h"
//#define TIM_DEBOUNCE		(htim6)
#define TIM_DEBOUNCE		(htim13)

/******************************************************************************
Debounce Struct
******************************************************************************/
typedef struct slidewindow
{
	uint8_t window;			// sliding window
	uint8_t count1s;		// count 1s in window

	GPIO_TypeDef* GPIOx;	// GPIO button port
	uint16_t GPIO_Pin;		// GPIO button pin

	uint8_t pin_output;		// button output
}ST_debounce;

extern ST_debounce button;
/******************************************************************************
Debounce Functions
******************************************************************************/
// start/stop debounce
void debounce_start(ST_debounce *s, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void debounce_stop(void);
// debounce ISR
void debounce_isr(void);

#endif /* __DEBOUNCE_H__ */
