#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"
#include <stdbool.h>

void DHT11_Init(void);
bool DHT11_Read(float *temperature, float *humidity);

#endif
