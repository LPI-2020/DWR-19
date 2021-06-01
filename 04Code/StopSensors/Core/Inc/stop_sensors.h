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
#define OBS_DETECTOR_TIM (htim6)
#define OBS_DETECTOR_ADC (hadc1)

/******************************************************************************
Define Parameters
******************************************************************************/
// Obstacle Detector Limit
#define ADC_DISTANCE_LIMIT (1139) // Digital value of 30 cm
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
Stop Sensors ISRs
******************************************************************************/
void stop_sensors_init(void);

void isr_obs_detector(void);

#endif /* !_STOP_SENSORS_H_ */
