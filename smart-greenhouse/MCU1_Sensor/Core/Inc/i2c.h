#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"
#include <stdint.h>

// 使用软件I2C，基于KPZ32手柄接口引脚
// PA15 - SDA (DAT)
// PA14 - SCL (CMD)

#define I2C_SDA_PORT    GPIOA
#define I2C_SDA_PIN     GPIO_Pin_15
#define I2C_SCL_PORT    GPIOA
#define I2C_SCL_PIN     GPIO_Pin_14

void I2C_Init_All(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(uint8_t data);
uint8_t I2C_ReceiveByte(uint8_t ack);
void I2C_Ack(void);
void I2C_NAck(void);
uint8_t I2C_WaitAck(void);

#endif
