#include "tests.h"

#include "move.h"
#include "lfollower.h"

#include "stop_sensors.h"
#include "motion.h"

#include "rfid-rc522.h"
#include "timeout.h"

#include "debounce.h"

#include "usart.h"
#include "parser.h"
#include "commands.h"

#include "stm32f7xx_hal.h"

void test_stop_sensor(void);
/******************************************************************************
Test Move module
******************************************************************************/
void test_move(float speed)
{
	  // test FORWARD movement
	  move_forward(speed);
	  HAL_Delay(5000);
	  move_stop();
	  HAL_Delay(2000);

	  // test BACKWARDS movement
	  move_backwards(speed);
	  HAL_Delay(5000);
	  move_stop();
	  HAL_Delay(2000);

	  // test rotate RIGHT
	  move_rotate(MOVE_RIGHT, speed);
	  HAL_Delay(5000);
	  move_stop();
	  HAL_Delay(2000);

	  // test rotate LEFT
	  move_rotate(MOVE_LEFT, speed);
	  HAL_Delay(5000);
	  move_stop();
	  HAL_Delay(2000);
}

/******************************************************************************
Test debounce module
******************************************************************************/
ST_debounce button;

#define USER_BTN_PORT	(GPIOC)
#define USER_BTN_PIN	(GPIO_PIN_8)

void test_debounce(void)
{
	debounce_init(&button, USER_BTN_PORT, USER_BTN_PIN);
	debounce_start();

//	while(button.pin_output == 0)
//		;
//
//	button.pin_output = 0;

	while(1)
	{
		if(button.pin_output)
		{
			// user button pressed
			toggle_led(LBLUE);
			button.pin_output = 0;
		}
	}

	debounce_stop();
}

/******************************************************************************
Test lineFollower module
******************************************************************************/
void test_lf_print_qtr(void)
{
	lfollower_print_sens();
	HAL_Delay(300);
}

int test_lf_rotate(move_dir_e dir)
{
	uint8_t err;

//	write_led(LBLUE, 1);
	err = lfollower_rotate(dir);
//	write_led(LBLUE, 0);

	return err;
}

/******************************************************************************
Test motion module
******************************************************************************/
void test_motion(void)
{
	// start movement
	motion_start();

	// while motion is ON
	while(motion_status == MOT_ON)
		;
}

void test_motion_rotate(void)
{
	// use test_motion()
	uint16_t led;

	motion_status = MOT_CROSS_FOUND;

	if(motion_status == MOT_CROSS_FOUND)
	{
		led = LBLUE;

		write_led(LBLUE, 1);
		motion_start();

		HAL_Delay(2000);

		motion_stop();
		write_led(LBLUE, 0);

		test_lf_rotate(MOVE_LEFT);
	}
	else if(motion_status == MOT_ROOM_FOUND)
		// Room found. enable GREEN LED
		led = LGREEN;
	else if(motion_status == MOT_HOLD)
		// Obstacle found. enable RED LED
		led = LRED;

	while(1)
	{
		toggle_led(led);
		HAL_Delay(500);
	}
}

/******************************************************************************
Test stop sensors module
******************************************************************************/
void test_stop_sensor(void)
{
	// use test_motion()

	// motion stopped
	if(motion_status == MOT_CROSS_FOUND)
		// Cross found. enable BLUE LED
		write_led(LBLUE, 1);
	else if(motion_status == MOT_ROOM_FOUND)
		// Room found. enable GREEN LED
		write_led(LGREEN, 1);
	else if(motion_status == MOT_HOLD)
		// Obstacle found. enable RED LED
		write_led(LRED, 1);
}

void test_obs_detector(void)
{
	// use test_motion()

	if(motion_status == MOT_HOLD)
		// obstacle in front
		write_led(LRED, 1);

	// wait for obstacle to move
	while(motion_status == MOT_HOLD)
		;

	// obstacle has been removed
	write_led(LRED, 0);
}

/******************************************************************************
Test RFID module
******************************************************************************/
rfid_t rfid_test = {
			.CardID = {0},
			.result = 0,
			.type = 0
};

int test_rfid(void)
{
	uint8_t status = -1;

	// start movement
	motion_start();

	// while there is no cross
	while(motion_status != MOT_CROSS_FOUND)
		;

	// begin RFID read. Enable BLUE LED
//	write_led(LBLUE, 1);

	HAL_Delay(1000);
	// restart movement
	motion_start();

	test_stop_sensor();

	// read RFID
	status = RFID_read(&rfid_test);
	// stop movement
	motion_stop();

	if(status != MI_OK)
		return -1;

	// RFID read ok. disable BLUE LED
//	write_led(LBLUE, 0);

	write_led(LGREEN, 1);
	status = lfollower_rotate(MOVE_LEFT);
	write_led(LGREEN, 0);

	return status;
}

/******************************************************************************
Test timeouts
******************************************************************************/
void test_timeout(uint8_t sec)
{
	timeout_start(sec);

	while(timeout_flag == 0)
		;

	toggle_led(LGREEN);
}

/******************************************************************************
Test Bluetooth
******************************************************************************/
void test_bluetooth(void)
{
	if(bluet_uart.Rx_flag)
	{
		UART_Receive(&bluet_uart); // Returns received char
		bluet_uart.Rx_flag = 0;
	}

	if(cmd_received)
	{
		exec_cmd((char *) bluet_uart.Rx_Buffer);

		cmd_received = 0;
		Rx_UART_init(&bluet_uart); // ready to begin reception
	}
}

/******************************************************************************
Test modules functions
******************************************************************************/
int test_modules(void)
{
	int err = 0;

//	test_move(0.7);

//	while(1)
//		test_lf_print_qtr();

//	while(1)
//		test_timeout(2);


//	test_motion();
//	test_stop_sensor();

//	test_obs_detector(); // lixo


//	test_lf_rotate(MOVE_LEFT);
//	test_motion_rotate();

	test_debounce();
	test_motion();
	test_stop_sensor();
//	err = test_rfid();

//	test_bluetooth();

	return err;
}
