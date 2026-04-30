/**
  ******************************************************************************
  * @file    nrf24l01.c
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   NRF24L01无线模块驱动（接收端）
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "nrf24l01.h"
#include "bsp_spi.h"
#include "bsp_gpio.h"

/* 外部延时函数 */
extern void Delay_ms(uint32_t nTime);

/* NRF24L01引脚操作宏 */
#define NRF_CSN_LOW()   GPIO_ResetBits(NRF_CSN_GPIO_PORT, NRF_CSN_GPIO_PIN)
#define NRF_CSN_HIGH()  GPIO_SetBits(NRF_CSN_GPIO_PORT, NRF_CSN_GPIO_PIN)
#define NRF_CE_LOW()    GPIO_ResetBits(NRF_CE_GPIO_PORT, NRF_CE_GPIO_PIN)
#define NRF_CE_HIGH()   GPIO_SetBits(NRF_CE_GPIO_PORT, NRF_CE_GPIO_PIN)

/* Private functions ---------------------------------------------------------*/
static uint8_t NRF_ReadReg(uint8_t reg)
{
    uint8_t value;
    NRF_CSN_LOW();
    BSP_SPI_TransferByte(reg);
    value = BSP_SPI_TransferByte(0xFF);
    NRF_CSN_HIGH();
    return value;
}

static void NRF_WriteReg(uint8_t reg, uint8_t value)
{
    NRF_CSN_LOW();
    BSP_SPI_TransferByte(reg | 0x20);
    BSP_SPI_TransferByte(value);
    NRF_CSN_HIGH();
}

static void NRF_WriteBuf(uint8_t reg, uint8_t *buf, uint8_t len)
{
    uint8_t i;
    NRF_CSN_LOW();
    BSP_SPI_TransferByte(reg | 0x20);
    for(i = 0; i < len; i++)
    {
        BSP_SPI_TransferByte(buf[i]);
    }
    NRF_CSN_HIGH();
}

/**
  * @brief  NRF24L01初始化（接收模式）
  * @param  None
  * @retval None
  */
void NRF24L01_Init(void)
{
    uint8_t addr[5] = NRF_ADDRESS;

    NRF_CE_LOW();
    Delay_ms(10);

    NRF_WriteReg(NRF_CONFIG, 0x0F);        // 接收模式，使能CRC，上电
    NRF_WriteReg(NRF_EN_AA, 0x01);         // 使能自动应答
    NRF_WriteReg(NRF_EN_RXADDR, 0x01);     // 使能接收通道0
    NRF_WriteReg(NRF_SETUP_AW, 0x03);      // 地址宽度5字节
    NRF_WriteReg(NRF_SETUP_RETR, 0x1A);    // 自动重发设置
    NRF_WriteReg(NRF_RF_CH, NRF_CHANNEL);  // 设置频道
    NRF_WriteReg(NRF_RF_SETUP, 0x07);      // 0dBm, 1Mbps

    NRF_WriteBuf(NRF_RX_ADDR_P0, addr, 5); // 设置接收地址
    NRF_WriteReg(NRF_RX_PW_P0, 32);        // 接收数据长度32字节

    NRF_CE_HIGH();  // 进入接收模式
}

/**
  * @brief  NRF24L01接收数据
  * @param  data: 数据缓冲区
  * @param  len: 数据长度
  * @retval true:成功 false:失败
  */
bool NRF24L01_Receive(uint8_t *data, uint8_t len)
{
    uint8_t status;
    uint8_t i;

    status = NRF_ReadReg(NRF_STATUS);

    /* 检查是否有数据接收 */
    if(status & 0x40)
    {
        NRF_CSN_LOW();
        BSP_SPI_TransferByte(NRF_CMD_R_RX_PAYLOAD);
        for(i = 0; i < len; i++)
        {
            data[i] = BSP_SPI_TransferByte(0xFF);
        }
        NRF_CSN_HIGH();

        /* 清除中断标志 */
        NRF_WriteReg(NRF_STATUS, status);

        return true;
    }

    return false;
}
