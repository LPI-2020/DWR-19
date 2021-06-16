/*
 * stop_sensors.c
 *
 * Stop Sensors
 *
 *  Created on: May 5, 2021
 */
#include "stop_sensors.h"
#include "errors.h"

/******************************************************************************
Define Test symbol
******************************************************************************/
//#define _DEBUG_

#ifdef _DEBUG_
	#include "usart.h"
	#include <stdio.h>
#endif // !_DEBUG_

/******************************************************************************
Private macros
******************************************************************************/
// returns true if obstacle is closer than ADC_DISTANCE_LIMIT -> obstacle found
// receives CURRENT distance to obstacle and PREVIOUS distance do obstacle
#define OBS_TOO_CLOSE(_dist_, _prev_dist_) (((_dist_) >= ADC_DISTANCE_LIMIT) &&		\
											((_prev_dist_) >= ADC_DISTANCE_LIMIT))

/******************************************************************************
Obstacle Detector variables
******************************************************************************/
// distance to obstacle (updated by DMA)
static uint32_t obs_distance = 0;
// stop detector status
volatile uint8_t stop_detector_status = 0;

/******************************************************************************
Obstacle Detector
******************************************************************************/
void stop_detector_init(void)
{
	if(stop_detector_status)
		// stop detector already started
		return;

	// start Obstacle detector ADC DMA
	HAL_ADC_Start_DMA(&OBS_DETECTOR_ADC_DMA, &obs_distance, 1);
	// stop detector enabled
	stop_detector_status = 1;
}

void stop_detector_deInit(void)
{
	if(stop_detector_status == 0)
		// stop detector already stopped
		return;

	// stop Obstacle detector ADC DMA
	HAL_ADC_Stop_DMA(&OBS_DETECTOR_ADC_DMA);
	// stop detector disabled
	stop_detector_status = 0;
}

/******************************************************************************
Stop Detector ISR

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
	static uint32_t old_obs_distance = 0;
	uint8_t obs_found_flag = 0;

	// is stop detector ON?
	if(stop_detector_status == 0)
		// return all ok
		return EXIT_SUCCESS;

	// ***** Check Stop Marks Detector *****
	// if SENSOR_L enabled sens = 0000 0001 (1)
	// if SENSOR_L disabled sens = 0000 0000 (0)
	sens = qtr_get_digital(ST_SENSOR_L);

	// rotate left one bit
	// SENSOR_L enabled: sens = 0000 0010
	// SENSOR_L disabled: sens = 0000 0000
	sens = sens << 1;

	// SENSOR_L enabled:
		// if SENSOR_R enabled sens = 0000 0011 (3)
		// if SENSOR_R disabled sens = 0000 0010 (2)
	sens += qtr_get_digital(ST_SENSOR_R);

	// both sensors enabled
	if((sens == sens_prev) && (sens == 3))
//	if(sens == 3)
		// return cross found error
		return E_ST_CROSS_FOUND;

	// current sensors value equal to the previous sensor values
	// and only one sensor enabled
//	else if((sens == sens_prev) && (sens != 0))
//		// return room found error
//		return E_ST_ROOM_FOUND;

	// ***** Check Obstacle Detector *****
	// Obstacle found flag update
	obs_found_flag = OBS_TOO_CLOSE(obs_distance, old_obs_distance);

#ifdef _DEBUG_
	char str[32];
	snprintf(str, sizeof(str), "Dist: %d, flag%d\n\r", (int)obs_distance,
														obs_found_flag);
	UART_puts(str);
#endif // !_DEBUG_

	// update old distance variable
	old_obs_distance = obs_distance;

	if(obs_found_flag)
		// return obstacle found error
		return E_ST_OBS_FOUND;

	// update sensors value
	sens_prev = sens;

	return EXIT_SUCCESS;
}
