/*
 * bluetooth.c
 *
 *  Created on: Jun 14, 2021
 */

#include "bluetooth.h"

#include "usart.h"
#include "commands.h"

bluet_state_t bluet_status = BLUET_N_INIT;

void bluet_receive(void)
{
	char err;
//	if(bluet_status != BLUET_READY)
//	{
//
//		bluet_status = BLUET_READY;
//	}

	// any byte received by bluetooth?
	if(bluet_uart.Rx_flag)
	{
		UART_Receive(&bluet_uart);
		bluet_uart.Rx_flag = 0;
	}
	// command received?
	if(cmd_received)
	{
		// parses and executes the command - returns 0 if valid
		err = exec_cmd((char *) bluet_uart.Rx_Buffer);

//		// command executed -> bluet_st = BLUET_OK
//		// command not executed -> BLUET_READY
//		bluet_status = (err == 0) ? BLUET_OK : BLUET_READY;

		cmd_received = 0;
		// prepares bluetooth to receive again
		Rx_UART_init(&bluet_uart);
	}
}
