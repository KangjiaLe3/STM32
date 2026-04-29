/**
  ******************************************************************************
  * @file    bsp_adc.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   ADC板级支持包头文件
  ******************************************************************************
  */

#ifndef __BSP_ADC_H
#define __BSP_ADC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* ADC通道定义 */
#define TEMT6000_ADC_CHANNEL    ADC_Channel_0  /* PA0 */
#define SOIL_ADC_CHANNEL        ADC_Channel_2  /* PA2 */

/* Exported functions --------------------------------------------------------*/
void BSP_ADC_Init(void);
uint16_t BSP_ADC_Read(uint8_t channel);
uint16_t BSP_ADC_ReadSoilMoisture(void);

#endif /* __BSP_ADC_H */
