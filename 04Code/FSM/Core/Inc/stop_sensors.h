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

// Sensors used on cross and room detectors:
// RIGHT sensor
#define SENSOR_R		(SENSOR1)
// LEFT sensor
#define SENSOR_L		(SENSOR8)

// Obstacle Detector Limit = Digital value of 30 cm
#define ADC_DISTANCE_LIMIT (1139)

/******************************************************************************
Stop Sensors Flags
******************************************************************************/
// Obstacle Found Flag
extern uint8_t obs_found_flag;
// Cross Found Flag
extern uint8_t cross_found_flag;
// Room Found Flag
extern uint8_t room_found_flag;

/******************************************************************************
Obstacle Detector Functions
******************************************************************************/
void obs_detector_init(void);
void obs_detector_deInit(void);
void isr_obs_detector(void);

/******************************************************************************
Cross and Room Detectors Functions
******************************************************************************/
//uint8_t cross_detector(void);
//uint8_t room_detector(void);
void stop_detector(void);

#endif /* !_STOP_SENSORS_H_ */
