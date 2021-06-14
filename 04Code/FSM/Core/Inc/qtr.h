#ifndef __QTR_H__
#define __QTR_H__

#include <stdint.h>

/******************************************************************************
QTR Peripherals
******************************************************************************/
#include "adc.h"
// ADC-DMA that stores QTR sensor values
#define ADC_QTR_DMA		(hadc3)

/******************************************************************************
QTR defines
******************************************************************************/
// Number of sensors in use
#define QTR_SENS_NUM 	(6)

// Minimum (analog, in volts) value of a digital value (0 or 1).
//#define ANALOG_HI_VOLT 	(2.45)
#define ANALOG_HI_VOLT 		(2.8)
//#define ANALOG_HI_VOLT 		(3)

/******************************************************************************
QTR struct
******************************************************************************/
// Sensor elements
typedef enum {
	// QTR RIGHT side
	SENSOR1,
	SENSOR3,	// Line Follower RIGHT Sensor
	SENSOR4,
	// QTR Middle
	SENSOR5,
	SENSOR6,	// Line Follower LEFT Sensor
	SENSOR8
	// QTR LEFT side
} qtr_e;

/******************************************************************************
QTR functions
******************************************************************************/
void qtr_init(void);
void qtr_kill(void);

float 	qtr_get_analog(qtr_e sensor);
uint8_t qtr_get_digital(qtr_e sensor);

#endif // !__QTR_H__
