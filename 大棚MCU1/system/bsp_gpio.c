/**
  ******************************************************************************
  * @file    bsp_gpio.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   GPIO板级支持包
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_gpio.h"

/**
  * @brief  GPIO初始化
  * @param  None
  * @retval None
  */
void BSP_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_AFIO, ENABLE);

    /* 禁用JTAG，保留SWD调试功能，释放PB3引脚 */
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    /* DHT11 (PA1) - 推挽输出 */
    GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);

    /* 继电器 (PB5) - 推挽输出 */
    GPIO_InitStructure.GPIO_Pin = RELAY_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(RELAY_GPIO_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(RELAY_GPIO_PORT, RELAY_GPIO_PIN);

    /* 蜂鸣器 (PB2) - 推挽输出 */
    GPIO_InitStructure.GPIO_Pin = BUZZER_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(BUZZER_GPIO_PORT, BUZZER_GPIO_PIN);

    /* 按键1 (PA8) - 上拉输入 */
    GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);

    /* 按键2 (PA11) - 上拉输入 */
    GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);

    /* NRF CE (PB0) - 推挽输出 */
    GPIO_InitStructure.GPIO_Pin = NRF_CE_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(NRF_CE_GPIO_PORT, &GPIO_InitStructure);

    /* NRF CSN (PA4) - 推挽输出 */
    GPIO_InitStructure.GPIO_Pin = NRF_CSN_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(NRF_CSN_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(NRF_CSN_GPIO_PORT, NRF_CSN_GPIO_PIN);

    /* NRF IRQ (PB1) - 上拉输入 */
    GPIO_InitStructure.GPIO_Pin = NRF_IRQ_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(NRF_IRQ_GPIO_PORT, &GPIO_InitStructure);

    /* I2C SDA (PB6) - 开漏输出 */
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(I2C_SDA_GPIO_PORT, I2C_SDA_GPIO_PIN);

    /* I2C SCL (PB7) - 开漏输出 */
    GPIO_InitStructure.GPIO_Pin = I2C_SCL_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
    GPIO_SetBits(I2C_SCL_GPIO_PORT, I2C_SCL_GPIO_PIN);
}
