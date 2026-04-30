/**
  ******************************************************************************
  * @file    oled.h
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   OLED显示屏驱动头文件
  ******************************************************************************
  */

#ifndef __OLED_H
#define __OLED_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdint.h>

/* OLED I2C地址 */
#define OLED_ADDR 0x78

/* Exported functions --------------------------------------------------------*/
void OLED_Init(void);
void OLED_Clear(void);
void OLED_SetPos(uint8_t x, uint8_t y);
void OLED_ShowChar(uint8_t x, uint8_t y, char chr);
void OLED_ShowString(uint8_t x, uint8_t y, char *str);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len);

#endif /* __OLED_H */
