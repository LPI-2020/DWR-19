#include "tests.h"
#include "move.h"
#include "lfollower.h"

#include "stm32f7xx_hal.h"

// Test move module functionalities
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

void test_lfollower(move_dir_e dir)
{
	uint8_t err;

	// rotate
	err = lfollower_rotate(dir);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, err & 0x01);
}
