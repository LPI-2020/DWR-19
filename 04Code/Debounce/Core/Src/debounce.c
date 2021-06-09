#include "debounce.h"

uint8_t debounce(ST_debounce *pb)
{
	uint8_t pin_sample;
	// sample pino - onde per interrupt

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

void init_debounce_struct(ST_debounce *s, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	s->window = 0xf;
	s->count1s = 4;
	s->GPIOx = GPIOx;
	s->GPIO_Pin = GPIO_Pin;
}
