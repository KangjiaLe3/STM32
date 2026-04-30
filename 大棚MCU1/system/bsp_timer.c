/**
  ******************************************************************************
  * @file    bsp_timer.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   定时器板级支持包（用于舵机PWM）
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_timer.h"

/**
  * @brief  定时器初始化（TIM2和TIM4用于舵机PWM）
  * @param  None
  * @retval None
  */
void BSP_Timer_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    /* 禁用JTAG，释放PB3引脚 */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    /* 配置PB3为复用推挽输出（TIM2_CH2） */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* 配置PB8和PB9为复用推挽输出（TIM4_CH3和TIM4_CH4） */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* TIM2时基配置：50Hz PWM (20ms周期) */
    TIM_TimeBaseStructure.TIM_Period = 20000 - 1;        /* ARR */
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;        /* PSC: 72MHz/72=1MHz */
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /* TIM2通道2 PWM配置 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500;                /* 初始脉宽1.5ms（中位） */
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

    /* 使能TIM2 */
    TIM_Cmd(TIM2, ENABLE);

    /* TIM4时基配置：50Hz PWM (20ms周期) */
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

    /* TIM4通道3 PWM配置 */
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    /* TIM4通道4 PWM配置 */
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

    /* 使能TIM4 */
    TIM_Cmd(TIM4, ENABLE);
}
