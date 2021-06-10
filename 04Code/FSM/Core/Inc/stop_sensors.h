/*
 * stop_sensors.h
 *
 *  Created on: May 5, 2021
 */

#ifndef _STOP_SENSORS_H_
#define _STOP_SENSORS_H_

#include "qtr.h"

/******************************************************************************
Define Peripherals in Use
******************************************************************************/
#include "adc.h"
#include "tim.h"
#include "gpio.h"

#define OBS_DETECTOR_TIM (htim3)
#define OBS_DETECTOR_ADC (hadc3)

#define STOP_DETECTOR_ADC (hadc1)
#define STOP_DETECTOR_TIM (htim6)
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

// Stop sensors pin values (0 or 1)
//extern uint8_t sensor1_val;
//extern uint8_t sensor8_val;

#define ST_SENS_NUM	(2)
extern uint32_t st_sens[ST_SENS_NUM];

/******************************************************************************
Stop Sensors Functions
******************************************************************************/
#define CROSS_DETECTED(void) ((GET_SENS_LOGVAL(SENSOR1) == 1) && (GET_SENS_LOGVAL(SENSOR8) == 1))
#define ROOM_DETECTED(void)	((GET_SENS_LOGVAL(SENSOR1) == 1) && (GET_SENS_LOGVAL(SENSOR8) == 0))

void obs_detector_init(void);
void obs_detector_deInit(void);

void stop_detector_init(void);
void stop_detector_deInit(void);

void isr_obs_detector(void);
//void isr_stop_detector(void);

#endif /* !_STOP_SENSORS_H_ */
