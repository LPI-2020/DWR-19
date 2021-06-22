/*
 * bluetooth.c
 *
 *  Created on: Jun 14, 2021
 */

#include "bluetooth.h"
#include "errors.h"
#include "cmdparser.h"

#include "route.h"
#include "usart.h"

#include "fsm.h"
#include <stdlib.h>

/******************************************************************************
Bluetooth Status Flag
******************************************************************************/
bluet_state_t bluet_status = BLUET_OFF;

/******************************************************************************
Bluetooth Receive
******************************************************************************/
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

/******************************************************************************
@function	Route Selection
@usage		RT

@brief	 	Selects a route for the robot to take
******************************************************************************/
char route_sel_cb(uint8_t argc, char** argv)
{
	if(argc != 2) // number of arguments invalid?
		return (char)(-EINVARG);

	// route number
	uint8_t route_num = atoi(argv[1]);

	if(route_num > NUM_ROUTES)
		return (char)(-EINVARG);

	// else, select route
	route_ptr = route_arr[route_num - 1];

	// command received with success
	bluet_status = BLUET_OK;

	return 0;
}

/******************************************************************************
@function	Init Receiving
@usage		INIT

@brief	 	Intializes the bluetooth receive
******************************************************************************/
char init_receive_cb(uint8_t argc, char** argv)
{
	if(argc != 1) // number of arguments invalid?
		return (char)(-EINVARG);

	// able to start receiving
	bluet_status = BLUET_RECEIVING;

	return 0;
}

/******************************************************************************
@function	start
@usage		S

@brief	 	Intializes the bluetooth receive
******************************************************************************/
char start_cb(uint8_t argc, char** argv)
{
	if(argc != 1) // number of arguments invalid?
		return (char)(-EINVARG);

	nstate = S_FLW_LINE;

	// command received with success
//	bluet_status = BLUET_OK;

	return 0;
}

/******************************************************************************
@function	movement
******************************************************************************/
char stop_cb(uint8_t argc, char** argv)
{
	if(argc != 1) // number of arguments invalid?
			return (char)(-EINVARG);

	remote_ctrl_dir = ACT_STOP;
	return 0;
}

char move_fw_cb(uint8_t argc, char** argv)
{
	if(argc != 1) // number of arguments invalid?
			return (char)(-EINVARG);

	remote_ctrl_dir = ACT_FORWARD;
	return 0;
}

char move_bw_cb(uint8_t argc, char** argv)
{
	if(argc != 1) // number of arguments invalid?
			return (char)(-EINVARG);

	remote_ctrl_dir = ACT_BACKWARD;
	return 0;
}

char move_right_cb(uint8_t argc, char** argv)
{
	if(argc != 1) // number of arguments invalid?
			return (char)(-EINVARG);

	remote_ctrl_dir = ACT_RIGHT;
	return 0;
}

char move_left_cb(uint8_t argc, char** argv)
{
	if(argc != 1) // number of arguments invalid?
			return (char)(-EINVARG);

	remote_ctrl_dir = ACT_LEFT;
	return 0;
}