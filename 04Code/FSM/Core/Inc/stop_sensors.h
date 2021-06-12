/*
 * stop_sensors.h
 *
 *  Created on: May 5, 2021
 */

#ifndef _STOP_SENSORS_H_
#define _STOP_SENSORS_H_

/******************************************************************************
Define Peripherals in Use
******************************************************************************/
#include "adc.h"
//#include "tim.h"

// Obstacle Detector Timer and ADC
//#define OBS_DETECTOR_TIM 		(htim6)
#define OBS_DETECTOR_ADC_DMA 	(hadc2)

/******************************************************************************
Define Parameters
******************************************************************************/
#include "qtr.h"

// Stop Detector RIGHT sensor
#define ST_SENSOR_R		(SENSOR1)
// Stop Detector LEFT sensor
#define ST_SENSOR_L		(SENSOR8)

// Obstacle Detector Limit = Digital value of 30 cm
#define ADC_DISTANCE_LIMIT (1139)

/******************************************************************************
Stop Sensors Errors
******************************************************************************/
#define EXIT_SUCCESS	0
#define E_CROSS_FOUND	1	// error cross found
#define E_ROOM_FOUND	2	// error room found
#define E_OBS_FOUND		3	// error obstacle found

/******************************************************************************
Obstacle Detector Functions
******************************************************************************/
void stop_detector_init(void);
void stop_detector_deInit(void);
uint8_t stop_detector_isr(void);

#endif /* !_STOP_SENSORS_H_ */
