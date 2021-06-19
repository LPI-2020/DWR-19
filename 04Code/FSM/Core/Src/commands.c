#include "commands.h"
#include "errors.h"

#include "usart.h" // UART_puts
#include <stdio.h> // snprintf

#include "bluetooth.h"

#include "fsm.h"

// Callbacks Includes

// Function Prototype
char help_cb(uint8_t argc, char** argv);
char route_sel_cb(uint8_t argc, char** argv);
char init_receive_cb(uint8_t argc, char** argv);
char start_cb(uint8_t argc, char** argv);
char stop_cb(uint8_t argc, char** argv);

/******************************************************************************
@name		cmd_list
@brief	 	List of commands, used in parsing. Each command is made of:
					- Command name
					- Command help text
					- Command callback function
******************************************************************************/
const Command_t cmd_list[] = 
{
	// Interface commands
	{ 
		"?",
		"Help text: Lists valid commands.",
		help_cb 
	},
	{
		"INIT",
		"Receive init: ",
		init_receive_cb
	},
	{
		"RT",
		"Route selection: ",
		route_sel_cb
	},
	{
		"S",
		"Start: ",
		start_cb
	},
	{
		"ST",
		"Stop: ",
		stop_cb
	},
	{ //end of Command list
		0,
		0,
		0
	},
};

/******************************************************************************
@function  exec_cmd
@param		 String inserted by user
@brief	 	 Parses string, executes commands and prints error message.
******************************************************************************/
char exec_cmd(const char *str)
{
	char err;

	err = parse_cmd(cmd_list, str);

	switch((char)(-err))
	{
		case ECMDNF:
			// No command found
			UART_puts(&bluet_uart,"Command [");
			UART_puts(&bluet_uart, str);
			UART_puts(&bluet_uart,"] not found.\n\r");
			break;

		case EINVARG:
			UART_puts(&bluet_uart,"Invalid arguments.\n\r");
			break;

	}

	return err;
}

/******************************************************************************
@function  Help
@usage		 ?

@brief	 	 Print a list of the valid commands
******************************************************************************/
char help_cb(uint8_t argc, char** argv)
{
	const Command_t *p = cmd_list;
	char str[128]; // Output message. Max message len is the same as buffer used in UART_puts
	
	if(argc != 1) // number of arguments invalid?
		//return (char)(-EINVARG);
		return (-1);
	
	UART_puts(&bluet_uart, "List of valid commands:\n\n\r");
	while(p->cmd)			
	{
		snprintf(str, sizeof(str), "%4s - %s\n\n\r", p->cmd, p->help);		// send the formated string to 'str' limiting the size to the size alocated for the string 'str'
		UART_puts(&bluet_uart, str);
		p++;
	}
	
	return 0;
}

/******************************************************************************
@function	Route Selection
@usage		RT

@brief	 	Selects a route for the robot to take
******************************************************************************/
char route_sel_cb(uint8_t argc, char** argv)
{
	if(argc != 2) // number of arguments invalid?
		//return (char)(-EINVARG);
		return (-1);

	// route selection
	route_ptr = route1;

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
		//return (char)(-EINVARG);
		return (-1);

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
		//return (char)(-EINVARG);
		return (-1);

	nstate = S_FLW_LINE;

	return 0;
}

/******************************************************************************
@function	stop
@usage		ST

@brief	 	Intializes the bluetooth receive
******************************************************************************/
char stop_cb(uint8_t argc, char** argv)
{
	if(argc != 1) // number of arguments invalid?
		//return (char)(-EINVARG);
		return (-1);

	nstate = S_STOPPED;

	return 0;
}

