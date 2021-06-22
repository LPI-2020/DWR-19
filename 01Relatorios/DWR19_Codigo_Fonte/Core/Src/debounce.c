#include "debounce.h"

/******************************************************************************
Debounce Start
******************************************************************************/
void debounce_start(debounce_t *s, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	// initialize sliding window
	s->sw.window = 0xf;
	s->sw.count1s = 4;

	s->GPIOx = GPIOx;
	s->GPIO_Pin = GPIO_Pin;

	s->pin_output = 0;

	// start Timer to interrupt
	HAL_TIM_Base_Start_IT(&TIM_DEBOUNCE);
}

/******************************************************************************
Debounce DeInit
******************************************************************************/
void debounce_stop(void)
{
	// stop timer
	HAL_TIM_Base_Stop_IT(&TIM_DEBOUNCE);
}

/******************************************************************************
Debounce ISR
******************************************************************************/
static uint8_t debounce(debounce_t *pb)
{
	uint8_t pin_sample;

	// sample pin - once per interrupt
	pin_sample = HAL_GPIO_ReadPin(pb->GPIOx, pb->GPIO_Pin);

	// apply sliding window
	sliding_window(pin_sample, &(pb->sw));

	// verify output
	return (((4 - pb->sw.count1s) >> 7) & 0x01);
}

void debounce_isr(void)
{
	// previous button state
	static uint8_t pre_state = 0;
	// current button state
	uint8_t state = 0;

	// debounce button
	state = debounce(&button);

	// determine button output
	button.pin_output = (state * ((~pre_state) & 0x01));

	// update previous button state
	pre_state = state;
}
