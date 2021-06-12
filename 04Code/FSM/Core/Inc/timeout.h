/*
 * timeout.h
 *
 * Timeouts Module
 *
 *  Created on: June 12, 2021
 */
#ifndef __TIMEOUT_H__
#define __TIMEOUT_H__

#include <stdint.h> // using uint8_t

/******************************************************************************
Timeout TIM - counts 1sec timeouts
******************************************************************************/
#include "tim.h"
#define TIM_TIMEOUTS	(htim3)

/******************************************************************************
Timeout Status Flag
******************************************************************************/
extern uint8_t timeout_flag;

/******************************************************************************
Timeout Functions
******************************************************************************/
void timeout_start(uint8_t time_sec);
void timeout_stop(void);
void timeout_isr(void);

#endif // !__TIMEOUT_H__
