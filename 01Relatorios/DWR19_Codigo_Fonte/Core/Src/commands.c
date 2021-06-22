#include "commands.h"
#include "errors.h"

#include "usart.h" // UART_puts
#include <stdio.h> // snprintf

#include "bluetooth.h"

// Function Prototypes
char help_cb(uint8_t argc, char** argv);

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
	{
		"FW",
		"Forward",
		move_fw_cb
	},
	{
		"BW",
		"Backwards",
		move_bw_cb
	},
	{
		"R",
		"Move right",
		move_right_cb
	},
	{
		"L",
		"Move left",
		move_left_cb
	},
	{ //end of Command list
		0,
		0,
		0
	},
};

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


