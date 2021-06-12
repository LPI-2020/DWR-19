#ifndef __QTR_H__
#define __QTR_H__

#include "auxiliares.h" // using DIG_TO_ANALOG

/******************************************************************************
QTR Peripherals
******************************************************************************/
#include "adc.h"
// ADC-DMA that stores QTR sensor values
#define ADC_QTR_DMA		(hadc3)

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

// Number of sensors in use
#define QTR_SENS_NUM (6)
// QTR Sensors array
extern uint32_t qtr_sens[QTR_SENS_NUM];

/******************************************************************************
QTR functions
******************************************************************************/
#define ANALOG_HI_VOLT (2.45)	// In Volts. Minimum (analog) value of a digital
								// value (0 or 1).
//#define ANALOG_HI_VOLT 2.8
// Get sensor logical value Macro
#define GET_SENS_LOGVAL(_sens_)  (DIG_TO_ANALOG(qtr_sens[_sens_]) > ANALOG_HI_VOLT)

void qtr_init(void);
void qtr_kill(void);

#endif // !__QTR_H__
