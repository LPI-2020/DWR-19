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
void stop_sensors_init(void)
{
	// start Obstacle detector timer
	HAL_TIM_Base_Start(&OBS_DETECTOR_TIM);
	// start Obstacle detector ADC
	HAL_ADC_Start_IT(&OBS_DETECTOR_ADC);
}

void stop_sensors_deInit(void)
{
	// start Obstacle detector timer
	HAL_TIM_Base_Stop(&OBS_DETECTOR_TIM);
	// start Obstacle detector ADC
	HAL_ADC_Stop_IT(&OBS_DETECTOR_ADC);
}

/******************************************************************************
Obstacle Detector

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
Stop mark detector

- Used in gpio.c at void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
  when (GPIO_Pin == PIN_A)

- An external interrupt is generated when PIN_A = 1. There this function is
  used to check PinB value.
******************************************************************************/
void isr_stop_detector(void)
{
	GPIO_PinState pinB;
	pinB = HAL_GPIO_ReadPin(PIN_B_PORT, PIN_B);

	cross_found_flag = pinB & 0x01;
	room_found_flag = (~pinB) & 0x01;
}

