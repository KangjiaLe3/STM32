/**
  ******************************************************************************
  * @file    dht11.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   DHT11温湿度传感器驱动头文件
  ******************************************************************************
  */

#ifndef __DHT11_H
#define __DHT11_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdbool.h>

/* Exported functions --------------------------------------------------------*/
void DHT11_Init(void);
bool DHT11_Read(float *temperature, float *humidity);

#endif /* __DHT11_H */
