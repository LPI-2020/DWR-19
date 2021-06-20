/*
 * bluetooth.h
 *
 *  Created on: Jun 14, 2021
 */

#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "stdint.h" // using uint8_t

/******************************************************************************
Bluetooth Enum
******************************************************************************/
typedef enum {
	BLUET_OK,				// Bluetooth received
	BLUET_READY,			// Bluetooth ready
	BLUET_RECEIVING,		// Bluetooth receiving
	BLUET_OFF				// Bluetooth not initialized
} bluet_state_t;

extern bluet_state_t bluet_status;

/******************************************************************************
Bluetooth Functions
******************************************************************************/
void bluet_receive(void);

char route_sel_cb(uint8_t argc, char** argv);
char init_receive_cb(uint8_t argc, char** argv);
char start_cb(uint8_t argc, char** argv);
char stop_cb(uint8_t argc, char** argv);

#endif /* __BLUETOOTH_H__ */
