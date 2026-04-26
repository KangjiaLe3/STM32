#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"
#include <stdint.h>

// SPI1引脚定义（用于NRF24L01）
// PA5 - SCK
// PA6 - MISO
// PA7 - MOSI
// PA4 - NSS/CSN (软件控制)

void SPI_Init_All(void);
uint8_t SPI_TransferByte(uint8_t data);

#endif
