#ifndef __TEMT6000_H
#define __TEMT6000_H

#include "stm32f10x.h"
#include <stdint.h>

void TEMT6000_Init(void);
uint16_t TEMT6000_Read(void);

#endif
