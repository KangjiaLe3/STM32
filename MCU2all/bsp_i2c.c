/**
  ******************************************************************************
  * @file    bsp_i2c.c
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   MCU2软件I2C板级支持包
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_i2c.h"

/* Private functions ---------------------------------------------------------*/
static void I2C_Delay(void)
{
    uint8_t i;
    for(i = 0; i < 10; i++);
}

/**
  * @brief  I2C初始化
  * @param  None
  * @retval None
  */
void BSP_I2C_Init(void)
{
    /* GPIO已在BSP_GPIO_Init中初始化 */
    I2C_SDA_H();
    I2C_SCL_H();
}

/**
  * @brief  I2C起始信号
  * @param  None
  * @retval None
  */
void BSP_I2C_Start(void)
{
    I2C_SDA_H();
    I2C_SCL_H();
    I2C_Delay();
    I2C_SDA_L();
    I2C_Delay();
    I2C_SCL_L();
}

/**
  * @brief  I2C停止信号
  * @param  None
  * @retval None
  */
void BSP_I2C_Stop(void)
{
    I2C_SDA_L();
    I2C_SCL_L();
    I2C_Delay();
    I2C_SCL_H();
    I2C_Delay();
    I2C_SDA_H();
    I2C_Delay();
}

/**
  * @brief  I2C发送应答
  * @param  None
  * @retval None
  */
void BSP_I2C_Ack(void)
{
    I2C_SDA_L();
    I2C_Delay();
    I2C_SCL_H();
    I2C_Delay();
    I2C_SCL_L();
    I2C_Delay();
}

/**
  * @brief  I2C发送非应答
  * @param  None
  * @retval None
  */
void BSP_I2C_NAck(void)
{
    I2C_SDA_H();
    I2C_Delay();
    I2C_SCL_H();
    I2C_Delay();
    I2C_SCL_L();
    I2C_Delay();
}

/**
  * @brief  I2C等待应答
  * @param  None
  * @retval 0:应答 1:非应答
  */
uint8_t BSP_I2C_WaitAck(void)
{
    uint8_t ack;
    I2C_SDA_H();
    I2C_Delay();
    I2C_SCL_H();
    I2C_Delay();
    ack = I2C_SDA_READ();
    I2C_SCL_L();
    return ack;
}

/**
  * @brief  I2C发送一个字节
  * @param  data: 要发送的数据
  * @retval None
  */
void BSP_I2C_SendByte(uint8_t data)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if(data & 0x80)
            I2C_SDA_H();
        else
            I2C_SDA_L();
        I2C_Delay();
        I2C_SCL_H();
        I2C_Delay();
        I2C_SCL_L();
        data <<= 1;
    }
}

/**
  * @brief  I2C接收一个字节
  * @param  ack: 1发送应答 0发送非应答
  * @retval 接收到的数据
  */
uint8_t BSP_I2C_ReceiveByte(uint8_t ack)
{
    uint8_t i, data = 0;
    I2C_SDA_H();
    for(i = 0; i < 8; i++)
    {
        data <<= 1;
        I2C_SCL_H();
        I2C_Delay();
        if(I2C_SDA_READ())
            data |= 1;
        I2C_SCL_L();
        I2C_Delay();
    }
    if(ack)
        BSP_I2C_Ack();
    else
        BSP_I2C_NAck();
    return data;
}
