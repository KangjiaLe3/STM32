#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

// DHT11引脚定义
#define DHT11_PORT      GPIOA
#define DHT11_PIN       GPIO_Pin_0

// 继电器引脚定义
#define RELAY_PORT      GPIOB
#define RELAY_PIN       GPIO_Pin_12

// 蜂鸣器引脚定义
#define BUZZER_PORT     GPIOB
#define BUZZER_PIN      GPIO_Pin_13

// 按键引脚定义
#define KEY1_PORT       GPIOB
#define KEY1_PIN        GPIO_Pin_14
#define KEY2_PORT       GPIOB
#define KEY2_PIN        GPIO_Pin_15

// NRF24L01引脚定义
#define NRF_CE_PORT     GPIOB
#define NRF_CE_PIN      GPIO_Pin_0
#define NRF_IRQ_PORT    GPIOB
#define NRF_IRQ_PIN     GPIO_Pin_1

void GPIO_Init_All(void);

#endif
