#include "commands.h"
//#include "error.h"

#include "usart.h" // UART_puts
#include <stdio.h> // snprintf

// Callbacks Includes
char route_sel_cb(uint8_t argc, char** argv);

// Function Prototype
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
		"RT",
		"Route selection: ",
		route_sel_cb
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
	
//	switch((char)(-err))
//	{
//		case ECMDNF:
//			// No command found
//			UART_puts("Command [");
//			UART_puts(Rx_Buffer);
//			UART_puts("] not found.\n\r");
//			break;
//
//		case EINVARG:
//			UART_puts("Invalid arguments.\n\r");
//			break;
//
//		case ENOCMD:
//			// Command is empty
//		case ENOMEM:
//			// Command list is empty
//		//case (char)(-ENOLIST):
//			// No memory available or bad allocation of memory
//			break;
//		case EPERM:
//			UART_puts("No permission.\n\r");
//			break;
//
//		case ENOKEY:
//			UART_puts("Required key not defined.\n\r");
//			break;
//		case EALREADY:
//			UART_puts("Operation already in progress.\n\r");
//			break;
//		case ENOP:
//			UART_puts("No operation in progress.\n\r");
//
//	}
	

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
	//char str[32]; // Output message. Max message len is the same as buffer used in UART_puts

	if(argc != 2) // number of arguments invalid?
		//return (char)(-EINVARG);
		return (-1);

	// ...select route... do something

//	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);

	return 0;
}


