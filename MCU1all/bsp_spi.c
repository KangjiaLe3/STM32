/**
  ******************************************************************************
  * @file    bsp_spi.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   SPI板级支持包
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_spi.h"

/**
  * @brief  SPI1初始化
  * @param  None
  * @retval None
  */
void BSP_SPI_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 使能SPI1和GPIOA时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);

    /* 配置SPI1引脚 */
    /* PA5(SCK) - 复用推挽输出 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* PA6(MISO) - 浮空输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* SPI1配置 */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    /* 使能SPI1 */
    SPI_Cmd(SPI1, ENABLE);
}

/**
  * @brief  SPI发送接收一个字节
  * @param  data: 要发送的数据
  * @retval 接收到的数据
  */
uint8_t BSP_SPI_TransferByte(uint8_t data)
{
    /* 等待发送缓冲区空 */
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

    /* 发送数据 */
    SPI_I2S_SendData(SPI1, data);

    /* 等待接收缓冲区非空 */
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

    /* 返回接收到的数据 */
    return SPI_I2S_ReceiveData(SPI1);
}
