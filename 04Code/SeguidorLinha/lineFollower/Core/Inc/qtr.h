#ifndef __QTR_H__
#define __QTR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef enum { SENSOR1, SENSOR2, SENSOR3, SENSOR4, SENSOR5, SENSOR6, SENSOR7, SENSOR8 } qtr_e;

uint32_t qtr[8];

#endif /*__QTR_H__*/