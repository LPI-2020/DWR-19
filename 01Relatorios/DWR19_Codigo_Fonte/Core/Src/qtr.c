#include "qtr.h"

#include "auxiliares.h" // using DIG_TO_ANALOG

/******************************************************************************
QTR Sensors array
******************************************************************************/
// QTR Sensors array
static uint32_t qtr_sens[QTR_SENS_NUM] = {0};

/******************************************************************************
QTR init

@brief 	Starts storing QTR sensor values
@param	none
@retval	none
******************************************************************************/
void qtr_init(void)
{
	HAL_ADC_Start_DMA(&ADC_QTR_DMA, qtr_sens, QTR_SENS_NUM);
}

/******************************************************************************
QTR kill

@brief 	Stops storing QTR sensor values
@param	none
@retval	none
******************************************************************************/
void qtr_kill(void)
{
	HAL_ADC_Stop_DMA(&ADC_QTR_DMA);
}

/******************************************************************************
QTR Sensor Value

@brief 	Returns QTR sensor digital/analog value
@param	Sensor
@retval	Digital/analog value of the requested sensor
******************************************************************************/
// QTR get sensor digital value
uint8_t qtr_get_digital(qtr_e sensor)
{
	return (DIG_TO_ANALOG(qtr_sens[sensor]) > ANALOG_HI_VOLT) & 0x01;
}

// QTR get sensor analog value
float qtr_get_analog(qtr_e sensor)
{
	return (DIG_TO_ANALOG(qtr_sens[sensor]));
}
