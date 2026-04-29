/**
  ******************************************************************************
  * @file    scd40.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   SCD40 CO2传感器驱动
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "scd40.h"
#include "bsp_i2c.h"

/* 外部延时函数 */
extern void Delay_ms(uint32_t nTime);

/**
  * @brief  SCD40初始化
  * @param  None
  * @retval None
  */
void SCD40_Init(void)
{
    Delay_ms(1000);

    /* 发送开始周期性测量命令 */
    BSP_I2C_Start();
    BSP_I2C_SendByte(SCD40_ADDR << 1);
    BSP_I2C_WaitAck();
    BSP_I2C_SendByte(0x21);
    BSP_I2C_WaitAck();
    BSP_I2C_SendByte(0xB1);
    BSP_I2C_WaitAck();
    BSP_I2C_Stop();
}

/**
  * @brief  读取SCD40 CO2浓度
  * @param  None
  * @retval CO2浓度(ppm)
  */
uint16_t SCD40_Read(void)
{
    uint16_t co2 = 0;
    uint8_t msb, lsb;

    /* 发送读取测量数据命令 */
    BSP_I2C_Start();
    BSP_I2C_SendByte(SCD40_ADDR << 1);
    BSP_I2C_WaitAck();
    BSP_I2C_SendByte(0xEC);
    BSP_I2C_WaitAck();
    BSP_I2C_SendByte(0x05);
    BSP_I2C_WaitAck();
    BSP_I2C_Stop();

    Delay_ms(1);

    /* 读取数据 */
    BSP_I2C_Start();
    BSP_I2C_SendByte((SCD40_ADDR << 1) | 1);
    BSP_I2C_WaitAck();

    msb = BSP_I2C_ReceiveByte(1);
    lsb = BSP_I2C_ReceiveByte(1);
    BSP_I2C_ReceiveByte(0);  /* CRC */

    BSP_I2C_Stop();

    co2 = (msb << 8) | lsb;
    return co2;
}
