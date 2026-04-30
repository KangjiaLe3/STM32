/**
  ******************************************************************************
  * @file    display.h
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   显示逻辑头文件
  ******************************************************************************
  */

#ifndef __DISPLAY_H
#define __DISPLAY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "protocol.h"

/* Exported functions --------------------------------------------------------*/
void Display_Init(void);
void Display_Update(SensorData_t *data);

#endif /* __DISPLAY_H */
