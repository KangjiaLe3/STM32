#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"
#include <stdint.h>

// 使用软件I2C，避开所有冲突引脚
// 避开：PA14/PA15(调试), PA5/PA6/PA7(SPI1), PA0/PA1/PA2(ADC/DHT11)
// 使用传感器S4接口的引脚
// PB0 - SDA (传感器S4接口)
// PA3 - SCL (传感器S4接口，原本分配给NRF CE，需要调整)

// 重新规划：
// 使用PB6和PB7（虽然图中标注为PWM舵机接口，但我们只用3个舵机，可以空出来）
#define I2C_SDA_PORT    GPIOB
#define I2C_SDA_PIN     GPIO_Pin_6
#define I2C_SCL_PORT    GPIOB
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
