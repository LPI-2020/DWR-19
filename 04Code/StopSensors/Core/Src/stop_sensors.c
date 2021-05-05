/*
 * stop_sensors.c
 *
 *  Created on: May 5, 2021
 */
#include "stop_sensors.h"
#include "usart.h"

#include <stdio.h>
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
void isr_obs_detector(void)
{
	static uint32_t distance;
	static uint32_t old_distance = 0;

	// read ADC value
	distance = HAL_ADC_GetValue(&OBS_DETECTOR_ADC);

	// Obstacle found flag update
	obs_found_flag = ((distance >= ADC_DISTANCE_LIMIT) && (old_distance >= ADC_DISTANCE_LIMIT));
	// update old distance variable
	old_distance = distance;

	// >>>>>>>>>>>>>>>><< Debug
	char str[16];
	snprintf(str, sizeof(str), "Dist: %d", (int)distance);
	UART_puts(str);
}

