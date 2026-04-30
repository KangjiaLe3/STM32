/**
  ******************************************************************************
  * @file    temt6000.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   TEMT6000光照传感器驱动
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "temt6000.h"
#include "bsp_adc.h"

/**
  * @brief  TEMT6000初始化
  * @param  None
  * @retval None
  */
void TEMT6000_Init(void)
{
    /* ADC已在BSP_ADC_Init中初始化 */
}

/**
  * @brief  读取TEMT6000光照强度
  * @param  None
  * @retval 光照强度ADC值(0-4095)
  */
uint16_t TEMT6000_Read(void)
{
    return BSP_ADC_Read(TEMT6000_ADC_CHANNEL);
}
