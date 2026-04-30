/**
  ******************************************************************************
  * @file    relay.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   继电器和蜂鸣器驱动头文件
  ******************************************************************************
  */

#ifndef __RELAY_H
#define __RELAY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported functions --------------------------------------------------------*/
void Relay_Init(void);
void Relay_On(void);
void Relay_Off(void);
void Buzzer_On(void);
void Buzzer_Off(void);

#endif /* __RELAY_H */
