#ifndef __DEBOUNCE_H__
#define __DEBOUNCE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f7xx_hal.h"

typedef struct slidewindow
{
	uint8_t window;
	uint8_t count1s;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}ST_debounce;

uint8_t debounce(ST_debounce *pb);
void init_debounce_struct(ST_debounce *s, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#ifdef __cplusplus
}
#endif

#endif /* __DEBOUNCE_H__ */
