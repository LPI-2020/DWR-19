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
#include "tim.h"

// Obstacle Detector Timer and ADC
#define OBS_DETECTOR_TIM (htim6)
#define OBS_DETECTOR_ADC (hadc2)

/******************************************************************************
Define Parameters
******************************************************************************/
#include "qtr.h"

// QTR Sensors used on cross and room detectors:
// RIGHT sensor
#define SENSOR_R		(SENSOR1)
// LEFT sensor
#define SENSOR_L		(SENSOR8)

// Obstacle Detector Limit = Digital value of 30 cm
#define ADC_DISTANCE_LIMIT (1139)

/******************************************************************************
Stop Sensors Errors
******************************************************************************/
#define EXIT_SUCCESS	0
#define E_CROSS_FOUND	1
#define E_ROOM_FOUND	2
#define E_OBS_FOUND		3

/******************************************************************************
Obstacle Detector Functions
******************************************************************************/
void stop_detector_init(void);
void stop_detector_deInit(void);
uint8_t stop_detector_isr(void);

#endif /* !_STOP_SENSORS_H_ */
