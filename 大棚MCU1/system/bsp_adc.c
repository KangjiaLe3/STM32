/**
  ******************************************************************************
  * @file    bsp_adc.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   ADC板级支持包
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_adc.h"

/**
  * @brief  ADC初始化
  * @param  None
  * @retval None
  */
void BSP_ADC_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能ADC1和GPIOA时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* 配置ADC时钟为PCLK2的6分频，即12MHz */
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    /* 配置PA0和PA2为模拟输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* ADC1配置 */
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* 使能ADC1 */
    ADC_Cmd(ADC1, ENABLE);

    /* 使能ADC1复位校准寄存器 */
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));

    /* 开始ADC1校准 */
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}

/**
  * @brief  读取ADC值
  * @param  channel: ADC通道
  * @retval ADC转换值
  */
uint16_t BSP_ADC_Read(uint8_t channel)
{
    /* 配置ADC通道 */
    ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_55Cycles5);

    /* 启动转换 */
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    /* 等待转换完成 */
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    /* 返回转换值 */
    return ADC_GetConversionValue(ADC1);
}

/**
  * @brief  读取土壤湿度ADC值
  * @param  None
  * @retval 土壤湿度ADC值
  */
uint16_t BSP_ADC_ReadSoilMoisture(void)
{
    return BSP_ADC_Read(SOIL_ADC_CHANNEL);
}
