#include "tests.h"
#include "move.h"

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
