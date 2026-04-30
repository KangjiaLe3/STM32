/**
  ******************************************************************************
  * @file    bsp_gpio.h
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   MCU2 GPIO板级支持包头文件
  ******************************************************************************
  */

#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

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

/* I2C引脚定义（软件I2C，用于OLED） */
#define I2C_SDA_GPIO_PORT    GPIOB
#define I2C_SDA_GPIO_PIN     GPIO_Pin_7
#define I2C_SDA_GPIO_CLK     RCC_APB2Periph_GPIOB

#define I2C_SCL_GPIO_PORT    GPIOB
#define I2C_SCL_GPIO_PIN     GPIO_Pin_6
#define I2C_SCL_GPIO_CLK     RCC_APB2Periph_GPIOB

/* Exported functions --------------------------------------------------------*/
void BSP_GPIO_Init(void);

#endif /* __BSP_GPIO_H */
