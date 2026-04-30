/**
  ******************************************************************************
  * @file    main.h
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   MCU2主程序头文件
  ******************************************************************************
  */

#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/* Exported functions --------------------------------------------------------*/
void SystemClock_Config(void);

/* 外部延时函数声明（用户已提供，基于SysTick） */
extern void Delay_ms(uint32_t nTime);

#endif /* __MAIN_H */
