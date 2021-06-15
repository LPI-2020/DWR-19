#include "debounce.h"

/******************************************************************************
Debounce Init

@brief
@param
@retval	none
******************************************************************************/
void debounce_init(ST_debounce *s, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	// init sliding window
	s->window = 0xf;
	s->count1s = 4;

	s->GPIOx = GPIOx;
	s->GPIO_Pin = GPIO_Pin;

	s->pin_output = 0;
}

/******************************************************************************
Debounce Start

@brief
@param
@retval	none
******************************************************************************/
void debounce_start(void)
{
	// start Timer to interrupt
	HAL_TIM_Base_Start_IT(&TIM_DEBOUNCE);
}

/******************************************************************************
Debounce DeInit

@brief
@param	none
@retval	none
******************************************************************************/
void debounce_stop(void)
{
	// stop timer
	HAL_TIM_Base_Stop_IT(&TIM_DEBOUNCE);
}

/******************************************************************************
Debounce ISR

@brief
@param	none
@retval	none
******************************************************************************/
static uint8_t debounce(ST_debounce *pb)
{
	uint8_t pin_sample;
	// sample pin - once per interrupt

	pin_sample = HAL_GPIO_ReadPin(pb->GPIOx, pb->GPIO_Pin);

	// refresh count1s
	// subtract window bit 7 to count1s
	pb->count1s -= (pb->window >> 7);
	// add pim_sample
	pb->count1s += pin_sample;

	// slide window
	pb->window <<=1;
	// put pin_sample bit 0 if window
	pb->window |= pin_sample;

	// verify output
	return (((4 - pb->count1s) >> 7) & 0x01);
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
//	if((pre_state == 0) && (state == 1))
//		button.pin_output = 0;
//	if((pre_state == 1) && (state == 0))
//		button.pin_output = 1;
	if((pre_state == 0) && (state == 1))
		button.pin_output = 1;
	if((pre_state == 1) && (state == 0))
		button.pin_output = 0;

	//button.pin_output = (~(state * ((~pre_state) & 0x01))) & 0x01;

	// update previous button state
	pre_state = state;
}
