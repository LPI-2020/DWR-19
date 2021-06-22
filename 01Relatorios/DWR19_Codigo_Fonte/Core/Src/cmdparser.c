#include "errors.h"
#include "parser.h"
#include "commands.h"

#include "usart.h"

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
