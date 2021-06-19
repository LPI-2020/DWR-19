/*
 * bluetooth.h
 *
 *  Created on: Jun 14, 2021
 */

#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "stdint.h"

typedef enum {
	BLUET_OK,				// Bluetooth received
	BLUET_READY,			// Bluetooth ready
	BLUET_RECEIVING,		// Bluetooth receiving
	BLUET_OFF				// Bluetooth not initialized
} bluet_state_t;

extern bluet_state_t bluet_status;

void bluet_receive(void);

#endif /* __BLUETOOTH_H__ */
