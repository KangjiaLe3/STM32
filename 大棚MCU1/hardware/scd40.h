/**
  ******************************************************************************
  * @file    scd40.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   SCD40 CO2传感器驱动头文件
  ******************************************************************************
  */

#ifndef __SCD40_H
#define __SCD40_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* SCD40 I2C地址 */
#define SCD40_ADDR 0x62

/* Exported functions --------------------------------------------------------*/
void SCD40_Init(void);
uint16_t SCD40_Read(void);

#endif /* __SCD40_H */
