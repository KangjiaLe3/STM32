/**
  ******************************************************************************
  * @file    relay.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   继电器和蜂鸣器驱动
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "relay.h"
#include "bsp_gpio.h"

/**
  * @brief  继电器和蜂鸣器初始化
  * @param  None
  * @retval None
  */
void Relay_Init(void)
{
    Relay_Off();
    Buzzer_Off();
}

/**
  * @brief  打开继电器
  * @param  None
  * @retval None
  */
void Relay_On(void)
{
    GPIO_SetBits(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
}

/**
  * @brief  关闭继电器
  * @param  None
  * @retval None
  */
void Relay_Off(void)
{
    GPIO_ResetBits(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
}

/**
  * @brief  打开蜂鸣器
  * @param  None
  * @retval None
  */
void Buzzer_On(void)
{
    GPIO_SetBits(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN);
}

/**
  * @brief  关闭蜂鸣器
  * @param  None
  * @retval None
  */
void Buzzer_Off(void)
{
    GPIO_ResetBits(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN);
}
