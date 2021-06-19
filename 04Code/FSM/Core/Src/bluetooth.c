/*
 * bluetooth.c
 *
 *  Created on: Jun 14, 2021
 */

#include "bluetooth.h"

#include "usart.h"
#include "commands.h"

bluet_state_t bluet_status = BLUET_OFF;

void bluet_receive(void)
{
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
		exec_cmd((char *) bluet_uart.Rx_Buffer);

		cmd_received = 0;
		// prepares bluetooth to receive again
		Rx_UART_init(&bluet_uart);
	}
}
