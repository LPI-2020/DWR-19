#ifndef __UCMD_H
#define __UCMD_H

//--------------------------------------//
// UCMD module for STM32F767						//
// Use in conjuction with UART3 module	//
//--------------------------------------//

#include "limits.h"
#include "stdint.h"

////////////////////////
// Define UCMD errors //
////////////////////////
#define UCMD_CMD_NOT_FOUND 						INT_MIN			
	
#define UCMD_NOT_ENOUGH_PARAMETERS 		INT_MIN+1

#define UCMD_CMD_LIST_NOT_FOUND 			INT_MIN+2

#define UCMD_MEM_NOT_VALID						INT_MIN+3

#define UCMD_PORT_NOT_VALID						INT_MIN+4

#define UCMD_ADC_CHANNEL_NOT_VALID 		INT_MIN+5

#define UCMD_CMD_LAST_CMD_LOOP				INT_MIN+6

#define UCMD_CMD_LAST_CMD_NOT_VALID 	INT_MIN+7

#define UCMD_COUNTER_VALUE_NOT_VALID	INT_MIN+8

#define UCMD_PARAMETERS_NOT_VALID			INT_MIN+9

//---------------------------------------------------------//

#define UCMD_DEFAULT_DELIMETER " "

typedef int (*Command_cb)(int, char* []);

typedef struct Command {
		const char *cmd;
		const char *help;
		Command_cb fn;
}Command;

////////////////////////////
// Declare Commands Below //
////////////////////////////

//Test Command

int led_on_cb (int, char* []);

//Memory Commands

int memory_read_cb (int, char* []);

int memory_write_cb (int, char* []);

//Pin commands

int make_pin_input_cb (int, char* []);

int make_pin_output_cb (int, char* []);

int read_dig_input_cb (int, char* []);

int write_dig_output_cb (int, char* []);

//Control Commands

int control_sys_cb(int argc, char* argv[]);

int enable_control_cb(int argc, char* argv[]);

int normalized_voltage_cb(int argc, char* argv[]);

int reference_speed_cb(int argc, char* argv[]);

int increase_control_cb(int argc, char* argv[]);
	
int decrease_control_cb(int argc, char* argv[]);

//Speed Capture Commands

int sampling_period_cb (int argc, char* argv[]);

int conversion_constant_cb (int argc, char* argv[]);

int sample_speed_cb (int argc, char* argv[]);

int stop_sampling_cb (int argc, char* argv[]);

//Extra Commands

int last_cmd_cb (int, char* []);

int help_cb (int, char* []);

int version_cb (int, char* []);

//---------------------------------------------------------//

//Parsing functions
int ucmd_parse(Command [], const char*, const char* in);

void ucmd_error_handler(int);

#endif
