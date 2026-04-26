#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"
#include <stdint.h>

void SPI_Init_All(void);
uint8_t SPI_TransferByte(uint8_t data);

#endif
