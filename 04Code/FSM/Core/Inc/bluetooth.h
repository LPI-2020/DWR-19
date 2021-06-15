/*
 * bluetooth.h
 *
 *  Created on: Jun 14, 2021
 */

#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "stdint.h"

typedef enum {
	BLUET_OK,
	BLUET_READY,
	BLUET_RECEIVING,
	BLUET_N_INIT
} bluet_state_t;

extern bluet_state_t bluet_status;

void bluet_receive(void);

#endif /* __BLUETOOTH_H__ */
