#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include <stdint.h>
#include <stdbool.h>

// 系统时钟配置
void SystemClock_Config(void);
void SysTick_Handler(void);
void delay_ms(uint32_t ms);
uint32_t millis(void);

// 外设初始化
void GPIO_Init_All(void);
void ADC_Init_All(void);
void TIM_Init_All(void);
void I2C_Init_All(void);
void SPI_Init_All(void);

#endif
