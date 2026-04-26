#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"
#include <stdint.h>

// 使用软件I2C，避开调试引脚
// 修正：不使用PA14(SWCLK)和PA15(JTDI)
// 改用传感器接口的空闲引脚
// PA6 - SDA (传感器S5接口)
// PA7 - SCL (传感器S6接口)

#define I2C_SDA_PORT    GPIOA
#define I2C_SDA_PIN     GPIO_Pin_6
#define I2C_SCL_PORT    GPIOA
#define I2C_SCL_PIN     GPIO_Pin_7

void I2C_Init_All(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(uint8_t data);
uint8_t I2C_ReceiveByte(uint8_t ack);
void I2C_Ack(void);
void I2C_NAck(void);
uint8_t I2C_WaitAck(void);

#endif
