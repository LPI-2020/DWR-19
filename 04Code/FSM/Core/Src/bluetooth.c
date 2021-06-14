/*
 * bluetooth.c
 *
 *  Created on: Jun 14, 2021
 */

#include "bluetooth.h"

#include "usart.h"

bluet_state_t bluet_st = BLUET_N_INIT;

bluet_state_t bluet_receive(void)
{
	char err;

	if(bluet_st != BLUET_READY)
		Rx_UART_init(&bluet_uart);

	// any byte received by bluetooth?
	if(bluet_uart.Rx_flag)
	{
		UART_Receive(&bluet_uart);
		bluet_uart.Rx_flag = 0;
		bluet_st = BLUET_RECEIVING;
	}
	// command received?
	if(cmd_received)
	{
		// parses and executes the command - returns 0 if valid
		err = exec_cmd((char *) bluet_uart.Rx_Buffer);

		// command executed -> bluet_st = BLUET_OK
		// command not executed -> BLUET_READY
		bluet_st = (err == 0) ? BLUET_OK : BLUET_READY;

		cmd_received = 0;
		// prepares bluetooth to receive again
		Rx_UART_init(&bluet_uart);
	}

	return bluet_st;
}
