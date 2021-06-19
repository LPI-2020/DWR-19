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

#define RFID_TIMEOUT		3	// RFID timeout time
#define ROTATE_TIMEOUT		4	// Rotate timeout time
#define PICK_UP_TIMEOUT 	5	// Pick up timeout time
#define HOLD_TIMEOUT		5	// Obstacle presence (hold) timeout time

/******************************************************************************
Timeout Status Flags
******************************************************************************/
extern volatile uint8_t rfid_timeout;
extern volatile uint8_t rotate_timeout;
extern volatile uint8_t pick_up_timeout;
extern volatile uint8_t hold_timeout;

extern volatile uint8_t rfid_timeout_ctrl,
		rotate_timeout_ctrl,
		pick_timeout_ctrl,
		hold_timeout_ctrl;

extern volatile uint8_t rfid_num_sec,
		rotate_num_sec,
		pick_num_sec,
		hold_num_sec;

/******************************************************************************
Timeout Functions
******************************************************************************/
void timeout_start(void);
void timeout_stop(void);
void timeout_isr(void);

#endif // !__TIMEOUT_H__
