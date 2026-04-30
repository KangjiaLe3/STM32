/**
  ******************************************************************************
  * @file    bsp_gpio.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   GPIO板级支持包头文件
  ******************************************************************************
  */

#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* DHT11引脚定义 (传感器S1接口) */
#define DHT11_GPIO_PORT      GPIOA
#define DHT11_GPIO_PIN       GPIO_Pin_1
#define DHT11_GPIO_CLK       RCC_APB2Periph_GPIOA

/* 继电器引脚定义 */
#define RELAY_GPIO_PORT      GPIOB
#define RELAY_GPIO_PIN       GPIO_Pin_5
#define RELAY_GPIO_CLK       RCC_APB2Periph_GPIOB

/* 蜂鸣器引脚定义 */
#define BUZZER_GPIO_PORT     GPIOB
#define BUZZER_GPIO_PIN      GPIO_Pin_2
#define BUZZER_GPIO_CLK      RCC_APB2Periph_GPIOB

/* 按键引脚定义 (KPZ32板载按键) */
#define KEY1_GPIO_PORT       GPIOA
#define KEY1_GPIO_PIN        GPIO_Pin_8
#define KEY1_GPIO_CLK        RCC_APB2Periph_GPIOA

#define KEY2_GPIO_PORT       GPIOA
#define KEY2_GPIO_PIN        GPIO_Pin_11
#define KEY2_GPIO_CLK        RCC_APB2Periph_GPIOA

/* NRF24L01引脚定义 */
#define NRF_CE_GPIO_PORT     GPIOB
#define NRF_CE_GPIO_PIN      GPIO_Pin_0
#define NRF_CE_GPIO_CLK      RCC_APB2Periph_GPIOB

#define NRF_CSN_GPIO_PORT    GPIOA
#define NRF_CSN_GPIO_PIN     GPIO_Pin_4
#define NRF_CSN_GPIO_CLK     RCC_APB2Periph_GPIOA

#define NRF_IRQ_GPIO_PORT    GPIOB
#define NRF_IRQ_GPIO_PIN     GPIO_Pin_1
#define NRF_IRQ_GPIO_CLK     RCC_APB2Periph_GPIOB

/* I2C引脚定义（软件I2C，用于SCD40） */
#define I2C_SDA_GPIO_PORT    GPIOB
#define I2C_SDA_GPIO_PIN     GPIO_Pin_6
#define I2C_SDA_GPIO_CLK     RCC_APB2Periph_GPIOB

#define I2C_SCL_GPIO_PORT    GPIOB
#define I2C_SCL_GPIO_PIN     GPIO_Pin_7
#define I2C_SCL_GPIO_CLK     RCC_APB2Periph_GPIOB

/* Exported functions --------------------------------------------------------*/
void BSP_GPIO_Init(void);

#endif /* __BSP_GPIO_H */
