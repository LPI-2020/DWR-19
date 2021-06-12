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
Obstacle Detector
******************************************************************************/
static uint32_t distance = 0; // >>>>>>>>>>>>>>>>>>>>>>>>>> use DMA

/******************************************************************************
Obstacle Detector
******************************************************************************/
void stop_detector_init(void)
{
	// start Obstacle detector timer
	HAL_TIM_Base_Start(&OBS_DETECTOR_TIM);
	// start Obstacle detector ADC
	//HAL_ADC_Start_IT(&OBS_DETECTOR_ADC);
	// start DMA to obstacle detector>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><
}

void stop_detector_deInit(void)
{
	// start Obstacle detector timer
	HAL_TIM_Base_Stop(&OBS_DETECTOR_TIM);
	// start Obstacle detector ADC
	//HAL_ADC_Stop_IT(&OBS_DETECTOR_ADC);
	// stop DMA to obstacle detector>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><
}

/******************************************************************************
Stop Detector

@brief 	Detects a cross if both sensors, SENSOR_R and SENSOR_L are over the line.
		Detects a room if one of the sensors, SENSOR_R or SENSOR_L is over the line.
		i.e, at logical state HIGH (GET_SENS_LOGVAL(SENSOR_x) == 1)
		Sens value 8 bits in form '0000 00LR':
		 	 - L (left sensor)
		 	 - R (right sensor)
@param	none
@retval	none
******************************************************************************/
uint8_t stop_detector_isr()
{
	// previous sensor values
	static uint8_t sens_prev = 0;
	// current sensor values
	uint8_t sens = 0;

	// Digital value of distance
	static uint32_t old_distance = 0;
	uint8_t obs_found_flag = 0;

	// ***** Check Stop Marks Detector *****
	// if SENSOR_L enabled sens = 0000 0001 (1)
	// if SENSOR_L disabled sens = 0000 0000 (0)
	sens = GET_SENS_LOGVAL(ST_SENSOR_L);

	// rotate left one bit
	// SENSOR_L enabled: sens = 0000 0010
	// SENSOR_L disabled: sens = 0000 0000
	sens = sens << 1;

	// SENSOR_L enabled:
		// if SENSOR_R enabled sens = 0000 0011 (3)
		// if SENSOR_R disabled sens = 0000 0010 (2)
	sens += GET_SENS_LOGVAL(ST_SENSOR_R);

	// both sensors enabled
	if(sens == 3)
		// return cross found error
		return E_CROSS_FOUND;

	// current sensors value equal to the previous sensor values
	// and only one sensor enabled
	else if((sens == sens_prev) && (sens != 0))
		// return room found error
		return E_ROOM_FOUND;

	// ***** Check Obstacle Detector *****
	// Obstacle found flag update
	obs_found_flag = ((distance >= ADC_DISTANCE_LIMIT) &&
						(old_distance >= ADC_DISTANCE_LIMIT));

#ifdef _DEBUG_
	char str[32];
	snprintf(str, sizeof(str), "Dist: %d, flag%d\n\r", (int)distance,
														obs_found_flag);
	UART_puts(str);
#endif // !_DEBUG_

	// update old distance variable
	old_distance = distance;

	if(obs_found_flag)
		// return obstacle found error
		return E_OBS_FOUND;

	// update sensors value
	sens_prev = sens;

	return EXIT_SUCCESS;
}
