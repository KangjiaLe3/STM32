#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"
#include <stdint.h>

void I2C_Init_All(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(uint8_t data);
uint8_t I2C_ReceiveByte(uint8_t ack);

#endif
