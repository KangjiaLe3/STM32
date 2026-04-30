/**
  ******************************************************************************
  * @file    main.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   主程序头文件
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include <stdbool.h>

/* Exported functions --------------------------------------------------------*/
void SystemClock_Config(void);

extern void Delay_ms(uint32_t nTime);

#endif /* __MAIN_H */
