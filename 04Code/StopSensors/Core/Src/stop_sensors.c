/*
 * stop_sensors.c
 *
 *  Created on: May 5, 2021
 */
#include "stop_sensors.h"
#include "usart.h"

#include <stdio.h>

/******************************************************************************
Define Test symbol
******************************************************************************/
#define _DEBUG_
/******************************************************************************
Stop Sensors Flags
******************************************************************************/
// Obstacle Found Flag
uint8_t obs_found_flag = 0;
// Cross Found Flag
uint8_t cross_found_flag = 0;
// Room Found Flag
uint8_t room_found_flag = 0;
/******************************************************************************
Functions
******************************************************************************/
void stop_sensors_init(void)
{
	// start Obstacle detector timer
	HAL_TIM_Base_Start(&OBS_DETECTOR_TIM);
	// start Obstacle detector ADC
	HAL_ADC_Start_IT(&OBS_DETECTOR_ADC);
}


void isr_obs_detector(void)
{
	// Digital value of distance
	static uint32_t distance;
	static uint32_t old_distance = 0;

	// read ADC value
	distance = HAL_ADC_GetValue(&OBS_DETECTOR_ADC);

	// Obstacle found flag update
	obs_found_flag = ((distance >= ADC_DISTANCE_LIMIT) &&
						(old_distance >= ADC_DISTANCE_LIMIT));
	// update old distance variable
	old_distance = distance;
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

#ifdef _DEBUG_
	char str[32];
	snprintf(str, sizeof(str), "Dist: %d, flag%d\n\r", (int)distance,
														obs_found_flag);
	UART_puts(str);
#endif // !_DEBUG_
}

