#include "tests.h"

#include "move.h"
#include "lfollower.h"

#include "stop_sensors.h"
#include "motion.h"

#include "rfid-rc522.h"
#include "timeout.h"

#include "stm32f7xx_hal.h"

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
Test lineFollower module
******************************************************************************/
void test_lf_print_qtr(void)
{
	lfollower_print_sens();
	HAL_Delay(300);
}

int test_lf_and_rotate(move_dir_e dir)
{
	// use test_stop_sensor() before

	// motion stopped
	// line follower only
	lfollower_start();
	HAL_Delay(1000);
	lfollower_stop();

	// rotate to dir
	return lfollower_rotate(dir);
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

/******************************************************************************
Test stop sensors module
******************************************************************************/
void test_stop_sensor(void)
{
	test_motion();

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
	test_motion();

	// wait for obstacle to move
	while(motion_status == MOT_HOLD)
		;

	test_motion();
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
	write_led(LBLUE, 1);

	//lfollower_start();
	// restart movement
	motion_start();
	// read RFID
	status = RFID_read(&rfid_test);
	//lfollower_stop();
	// stop movement
	motion_stop();

	if(status != MI_OK)
		return -1;

	// RFID read ok. disable BLUE LED
	write_led(LBLUE, 0);

	return lfollower_rotate(MOVE_LEFT);
}

/******************************************************************************
Test timeouts
******************************************************************************/
void test_timeout(uint8_t sec)
{
	timeout_start(sec);

	while(timeout_flag == 0)
		;

	toggle_led(LBLUE);
//	while(1)
//		;
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

	while(1)
		test_timeout(10);

//	test_motion();

	test_stop_sensor();
//	test_obs_detector();


//	err = lfollower_rotate(MOVE_RIGHT);
//
//	err = test_lf_and_rotate(MOVE_LEFT);
//
//	err = test_rfid();

	return err;
}
