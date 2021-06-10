#include "tests.h"
#include "stop_sensors.h"
#include "lfollower.h"

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

void test_lfollower_rotate(move_dir_e dir)
{
	uint8_t err;

	// rotate to direction dir
	err = lfollower_rotate(dir);

	// write LED RED pin if rotate is not completed
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, err & 0x01);
}

/******************************************************************************
Test stop sensors module
******************************************************************************/
void test_stop_sensor(uint8_t val)
{
	uint8_t err = 0;

	while(err != val)
		err = lfollower_control();

	// stop movement
	lfollower_stop();
}

/******************************************************************************
Test modules functions
******************************************************************************/
void test_modules(void)
{
	//test_move(0.7);
	//test_lfollower_rotate(MOVE_RIGHT);
	//test_print_qtr();
	//lfollower_start();

	test_stop_sensor(E_ROOM_FOUND);
	//test_stop_sensor(E_CROSS_FOUND);
}
