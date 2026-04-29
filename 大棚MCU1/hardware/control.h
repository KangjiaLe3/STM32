/**
  ******************************************************************************
  * @file    control.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   控制逻辑头文件
  ******************************************************************************
  */

#ifndef __CONTROL_H
#define __CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "protocol.h"
#include <stdbool.h>

/* Exported functions --------------------------------------------------------*/
void Control_Init(void);
void Control_AutoMode(SensorData_t *data);
void Control_ManualMode(SensorData_t *data);
void Control_SetMode(uint8_t mode);
uint8_t Control_GetMode(void);

#endif /* __CONTROL_H */
