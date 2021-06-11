#include "tests.h"
#include "stop_sensors.h"
#include "lfollower.h"
#include "rfid-rc522.h"

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
void test_print_qtr(void)
{
	lfollower_print_sens();
	HAL_Delay(300);
}

int test_lfollower_rotate(move_dir_e dir)
{
	uint8_t err;

	// rotate to direction dir
	err = lfollower_rotate(dir);

	return err;
	// write LED RED pin if rotate is not completed
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, err & 0x01);
}

int test_lfollower_and_rotate(void)
{
	uint8_t err = 0;

	while(err == 0)
		err = lfollower_control();

	// signal ERROR found through LED RED
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);

	lfollower_start();
	HAL_Delay(500);
	lfollower_stop();

	// rotate to direction dir
	err = lfollower_rotate(MOVE_LEFT);

	while(err == 0)
			err = lfollower_control();

	return 0;
	// write LED RED pin if rotate is not completed
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, err & 0x01);
}

/******************************************************************************
Test stop sensors module
******************************************************************************/
int test_stop_sensor()
{
	lfollower_start();

	while((!room_found_flag) && (!cross_found_flag))
		;

	// stop movement
	lfollower_stop();

	if(cross_found_flag)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);
	else if(room_found_flag)
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);

	return 0;
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
	uint8_t err = 0;

	// follow line
	lfollower_start();

	while((!room_found_flag) && (!cross_found_flag))
		;

	// begin RFID read
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1);

	lfollower_start();
	status = read_RFID(&rfid_test);
	lfollower_stop();

	if(status != MI_OK)
		return -1;

	// RFID read ok
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0);

	// else status = MI_OK
	//HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
	err = lfollower_rotate(MOVE_LEFT);

	return err;
}

/******************************************************************************
Test modules functions
******************************************************************************/
int test_modules(void)
{
	int err = 0;

	//test_move(0.7);

	//while(1)
		//test_print_qtr();

	//lfollower_start();

	//err = test_lfollower_rotate(MOVE_RIGHT);
	//err = test_lfollower_and_rotate();

	//err = test_stop_sensor(E_ROOM_FOUND);
	//err = test_stop_sensor(E_CROSS_FOUND);

	//err = test_rfid();
	test_stop_sensor();

	return err;
}
