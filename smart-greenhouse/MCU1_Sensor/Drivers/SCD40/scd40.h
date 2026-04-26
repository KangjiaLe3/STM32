#ifndef __SCD40_H
#define __SCD40_H

#include "stm32f10x.h"
#include <stdint.h>

#define SCD40_ADDR 0x62

void SCD40_Init(void);
uint16_t SCD40_Read(void);

#endif
