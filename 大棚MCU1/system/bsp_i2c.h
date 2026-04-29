/**
  ******************************************************************************
  * @file    bsp_i2c.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   软件I2C板级支持包头文件
  ******************************************************************************
  */

#ifndef __BSP_I2C_H
#define __BSP_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* I2C引脚操作宏 */
#define I2C_SDA_H()  GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define I2C_SDA_L()  GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define I2C_SCL_H()  GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define I2C_SCL_L()  GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define I2C_SDA_READ() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)

/* Exported functions --------------------------------------------------------*/
void BSP_I2C_Init(void);
void BSP_I2C_Start(void);
void BSP_I2C_Stop(void);
void BSP_I2C_SendByte(uint8_t data);
uint8_t BSP_I2C_ReceiveByte(uint8_t ack);
void BSP_I2C_Ack(void);
void BSP_I2C_NAck(void);
uint8_t BSP_I2C_WaitAck(void);

#endif /* __BSP_I2C_H */
