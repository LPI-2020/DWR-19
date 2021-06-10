#include "qtr.h"

/******************************************************************************
QTR Sensors array
******************************************************************************/
uint32_t qtr_sens[QTR_SENS_NUM];

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
