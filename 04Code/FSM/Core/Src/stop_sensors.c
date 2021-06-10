/*
 * stop_sensors.c
 *
 *  Created on: May 5, 2021
 */
#include "stop_sensors.h"
#include "auxiliares.h"

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
//uint8_t cross_found_flag = 0;
// Room Found Flag
//uint8_t room_found_flag = 0;

//uint8_t sensor1_val = 0;
//uint8_t sensor8_val = 0;

uint32_t st_sens[ST_SENS_NUM];

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
Stop mark Detector
******************************************************************************/
void stop_detector_init(void)
{
	// start sampling stop sensors values
//	HAL_TIM_Base_Start_IT(&STOP_DETECTOR_TIM);
	// start storing stop sensors values
	HAL_ADC_Start_DMA(&STOP_DETECTOR_ADC, st_sens, ST_SENS_NUM);
}

void stop_detector_deInit(void)
{
	// stop storing stop sensors values
	HAL_ADC_Stop_DMA(&STOP_DETECTOR_ADC);
	// stop sampling stop sensors values
//	HAL_TIM_Base_Stop_IT(&STOP_DETECTOR_TIM);
}

/******************************************************************************
Stop mark detector ISR

- Used in gpio.c at void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
******************************************************************************/

//typedef enum{
//	SENSOR1 = 0,
//	SENSOR8
//} st_sensor_e;
//
//
//
//void isr_stop_detector(void)
//{
//	// get stop sensors pin value (0 or 1)
//	sensor1_val = (DIG_TO_ANALOG(st_sens[SENSOR1]) > ANALOG_STOP_VOLT);
//	sensor8_val = (DIG_TO_ANALOG(st_sens[SENSOR8]) > ANALOG_STOP_VOLT);
//
//#ifdef _DEBUG_
//	char str[32];
//	snprintf(str, sizeof(str), "S1[%f]\n\rS8[%f]\n\r\n\r", DIG_TO_ANALOG(st_sens[0]),
//														   DIG_TO_ANALOG(st_sens[1]));
//	//snprintf(str, sizeof(str), "S1_val[%d]\n\rS8_val[%d]\n\r\n\r", sensor1_val, sensor8_val);
//
//	UART_puts(str);
//#endif //!_DEBUG_
//
//	// set stop sensors flags
//	// cross_found -> both stop sensors over the line (pin val = 1)
//	cross_found_flag = (sensor1_val & sensor8_val);
//	// room_found -> only one sensor over the line
//	room_found_flag = (sensor1_val);
//}

//void isr_stop_detector(void)
//{
//	(DIG_TO_ANALOG(st_sens[dir & 0x01]) < ANALOG_STOP_VOLT)
//
//}
