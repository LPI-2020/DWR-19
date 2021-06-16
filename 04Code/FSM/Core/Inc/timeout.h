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
//extern volatile uint8_t timeout_flag;

#define RFID_TIMEOUT	3	// RFID timeout time
#define ROTATE_TIMEOUT	4	// rotate timeout time
#define PICK_UP_TIMEOUT 20	// Pick up (of the object in each room) timeout time
#define HOLD_TIMEOUT		(15)

extern volatile uint8_t 	rfid_timeout,
							rotate_timeout,
							pick_up_timeout,
							hold_timeout;

extern uint8_t rfid_timeout_ctrl,
		rotate_timeout_ctrl,
		pick_timeout_ctrl,
		hold_timeout_ctrl;

/******************************************************************************
Timeout Functions
******************************************************************************/
//void timeout_start(int time_sec);
void timeout_start(void);
void timeout_stop(void);
void timeout_isr(void);

#endif // !__TIMEOUT_H__
