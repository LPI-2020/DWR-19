#ifndef __QTR_H__
#define __QTR_H__

/******************************************************************************
QTR Peripherals
******************************************************************************/
#include "adc.h"
#define ADC_QTR_DMA	(hadc1)
/******************************************************************************
QTR struct
******************************************************************************/
// Sensor elements
typedef enum {
	SENSOR1,
	SENSOR3,	// Line Follower RIGHT Sensor
	SENSOR4,	// Rotate RIGHT Sensor
	SENSOR5,	// Rotate LEFT Sensor
	SENSOR6,		// Line Follower LEFT Sensor
	SENSOR8
} qtr_e;

// Number of sensors in use
#define QTR_SENS_NUM (6)
// QTR Sensors array
extern uint32_t qtr_sens[QTR_SENS_NUM];

/******************************************************************************
QTR functions
******************************************************************************/
#define ANALOG_HI_VOLT (2.45)

#define GET_SENS_LOGVAL(_sens_)  (DIG_TO_ANALOG(qtr_sens[_sens_]) > ANALOG_HI_VOLT)

void qtr_init(void);
void qtr_kill(void);

#endif // !__QTR_H__
