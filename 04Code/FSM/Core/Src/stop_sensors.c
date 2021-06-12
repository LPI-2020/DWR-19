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
void stop_detector(void)
{
	// previous sensor values
	static uint8_t sens_prev = 0;
	// current sensor values
	uint8_t sens = 0;

	// if SENSOR_L enabled sens = 0000 0001 (1)
	// if SENSOR_L disabled sens = 0000 0000 (0)
	sens = GET_SENS_LOGVAL(SENSOR_L);

	// rotate left one bit
	// SENSOR_L enabled: sens = 0000 0010
	// SENSOR_L disabled: sens = 0000 0000
	sens = sens << 1;

	// SENSOR_L enabled:
		// if SENSOR_R enabled sens = 0000 0011 (3)
		// if SENSOR_R disabled sens = 0000 0010 (2)
	sens += GET_SENS_LOGVAL(SENSOR_R);

	// both sensors enabled
	if(sens == 3)
		cross_found_flag = 1;

	// current sensors value equal to the previous sensor values
	// 		and only one sensor enabled
	else if((sens == sens_prev) && (sens != 0))
	{
		room_found_flag = 1;
		//sens_prev = 0;
	}

	sens_prev = sens;
}

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

uint8_t stop_detector_isr()
{
	// previous sensor values
	static uint8_t sens_prev = 0;
	// current sensor values
	uint8_t sens = 0;

	// Digital value of distance
	static uint32_t distance = 0; // >>>>>>>>>>>>>>>>>>>>>>>>>> use DMA
	static uint32_t old_distance = 0;


	// ***** Check Stop Marks Detector *****
	// if SENSOR_L enabled sens = 0000 0001 (1)
	// if SENSOR_L disabled sens = 0000 0000 (0)
	sens = GET_SENS_LOGVAL(SENSOR_L);

	// rotate left one bit
	// SENSOR_L enabled: sens = 0000 0010
	// SENSOR_L disabled: sens = 0000 0000
	sens = sens << 1;

	// SENSOR_L enabled:
		// if SENSOR_R enabled sens = 0000 0011 (3)
		// if SENSOR_R disabled sens = 0000 0010 (2)
	sens += GET_SENS_LOGVAL(SENSOR_R);

	// both sensors enabled
	if(sens == 3)
		return E_CROSS_FOUND;

	// current sensors value equal to the previous sensor values
	// 		and only one sensor enabled
	else if((sens == sens_prev) && (sens != 0))
		return E_ROOM_FOUND;

	// ***** Check Obstacle Detector *****
	// Obstacle found flag update
	obs_found_flag = ((distance >= ADC_DISTANCE_LIMIT) &&
						(old_distance >= ADC_DISTANCE_LIMIT));

	// update old distance variable
	old_distance = distance;

	if(obs_found_flag)
		return E_OBS_FOUND;

	sens_prev = sens;

	return EXIT_SUCCESS;
}

///******************************************************************************
//Cross Detector
//
//@brief 	Detects a room if only SENSOR_R is above the line, logical state HIGH
//		with SENSOR_L at logical state LOW.
//@param	none
//@retval	Room found flag
//******************************************************************************/
//uint8_t room_detector(void)
//{
//	// check if SENSOR_R is over the line (logical state HIGH) and SENSOR_L isnt.
//	return (room_found_flag = ((GET_SENS_LOGVAL(SENSOR_R) == 1) &&
//			(GET_SENS_LOGVAL(SENSOR_L) == 0)));
//}
