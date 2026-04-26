#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

// DHT11引脚定义 (传感器S1接口)
#define DHT11_PORT      GPIOA
#define DHT11_PIN       GPIO_Pin_1

// 继电器引脚定义
#define RELAY_PORT      GPIOB
#define RELAY_PIN       GPIO_Pin_5

// 蜂鸣器引脚定义
#define BUZZER_PORT     GPIOB
#define BUZZER_PIN      GPIO_Pin_2

// 按键引脚定义 (KPZ32板载按键)
#define KEY1_PORT       GPIOA
#define KEY1_PIN        GPIO_Pin_8
#define KEY2_PORT       GPIOA
#define KEY2_PIN        GPIO_Pin_11

// NRF24L01引脚定义 (使用SPI1)
// 需要根据实际连接配置
#define NRF_CE_PORT     GPIOA
#define NRF_CE_PIN      GPIO_Pin_4
#define NRF_CSN_PORT    GPIOA
#define NRF_CSN_PIN     GPIO_Pin_4
#define NRF_IRQ_PORT    GPIOB
#define NRF_IRQ_PIN     GPIO_Pin_1

void GPIO_Init_All(void);

#endif
