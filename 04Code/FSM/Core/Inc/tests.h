/*
 * tests.h
 *
 * Tests module
 *
 *  Created on: June 7, 2021
 */
#ifndef __TESTS_H__
#define __TESTS_H__

/******************************************************************************
GPIO pins: LEDs used for testing
******************************************************************************/
#include "gpio.h"
// leds in GPIO Port B

#define LRED	(GPIO_PIN_14)
#define LBLUE	(GPIO_PIN_7)
#define LGREEN	(GPIO_PIN_0)

#define write_led(_pin_, _pinval_)	HAL_GPIO_WritePin(GPIOB, _pin_, _pinval_)
#define toggle_led(_pin_)			HAL_GPIO_TogglePin(GPIOB, _pin_)

/******************************************************************************
Test modules
******************************************************************************/
int test_modules(void);

#endif // !__TESTS_H__
