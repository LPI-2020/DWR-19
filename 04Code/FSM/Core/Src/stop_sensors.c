/*
 * stop_sensors.c
 *
 *  Created on: May 5, 2021
 */
#include "stop_sensors.h"

/******************************************************************************
Define Test symbol
******************************************************************************/
//#define _DEBUG_

#ifdef _DEBUG_
	#include "usart.h"
	#include <stdio.h>
#endif // !_DEBUG_
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
Obstacle Detector
******************************************************************************/
void obs_detector_init(void)
{
	// start Obstacle detector timer
	HAL_TIM_Base_Start(&OBS_DETECTOR_TIM);
	// start Obstacle detector ADC
	HAL_ADC_Start_IT(&OBS_DETECTOR_ADC);
}

void obs_detector_deInit(void)
{
	// start Obstacle detector timer
	HAL_TIM_Base_Stop(&OBS_DETECTOR_TIM);
	// start Obstacle detector ADC
	HAL_ADC_Stop_IT(&OBS_DETECTOR_ADC);
}

/******************************************************************************
Obstacle Detector ISR

- Used in adc.c at void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
  when (hadc->Instance == OBS_DETECTOR_ADC)

- Receives distance to near object by ADC
- The closer the object is to the sensor, the higher value will be measured
  by the sensor.
- ADC_DISTANCE_LIMIT is the limit that defines that an object has been found.
******************************************************************************/
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

#ifdef _DEBUG_
	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); // ## debug <- remove this pin

	char str[32];
	snprintf(str, sizeof(str), "Dist: %d, flag%d\n\r", (int)distance,
														obs_found_flag);
	UART_puts(str);
#endif // !_DEBUG_
}

/******************************************************************************
Cross Detector

@brief 	Detects a cross if both sensors, SENSOR_R and SENSOR_L are over the line.
		i.e, at logical state HIGH (GET_SENS_LOGVAL(SENSOR_x) == 1)
@param	none
@retval	Cross found flag
******************************************************************************/
uint8_t cross_detector(void)
{
	// check if both sensors are above the line, at logical state HIGH
	return (cross_found_flag = ((GET_SENS_LOGVAL(SENSOR_R) == 1) &&
			(GET_SENS_LOGVAL(SENSOR_L) == 1)));
}

/******************************************************************************
Cross Detector

@brief 	Detects a room if only SENSOR_R is above the line, logical state HIGH
		with SENSOR_L at logical state LOW.
@param	none
@retval	Room found flag
******************************************************************************/
uint8_t room_detector(void)
{
	// check if SENSOR_R is over the line (logical state HIGH) and SENSOR_L isnt.
	return (room_found_flag = ((GET_SENS_LOGVAL(SENSOR_R) == 1) &&
			(GET_SENS_LOGVAL(SENSOR_L) == 0)));
}
