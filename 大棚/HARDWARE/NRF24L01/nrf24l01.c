/**
  ******************************************************************************
  * @file    nrf24l01.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   NRF24L01无线模块驱动
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "nrf24l01.h"
#include "bsp_spi.h"
#include "bsp_gpio.h"
#include "config.h"

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
  * @brief  NRF24L01初始化
  * @param  None
  * @retval None
  */
void NRF24L01_Init(void)
{
    uint8_t addr[5] = NRF_ADDRESS;

    NRF_CE_LOW();
    Delay_ms(10);

    NRF_WriteReg(NRF_CONFIG, 0x0E);
    NRF_WriteReg(NRF_EN_AA, 0x01);
    NRF_WriteReg(NRF_EN_RXADDR, 0x01);
    NRF_WriteReg(NRF_SETUP_AW, 0x03);
    NRF_WriteReg(NRF_SETUP_RETR, 0x1A);
    NRF_WriteReg(NRF_RF_CH, NRF_CHANNEL);
    NRF_WriteReg(NRF_RF_SETUP, 0x07);

    NRF_WriteBuf(NRF_TX_ADDR, addr, 5);
    NRF_WriteBuf(NRF_RX_ADDR_P0, addr, 5);
    NRF_WriteReg(NRF_RX_PW_P0, 32);

    NRF_CE_HIGH();
}

/**
  * @brief  NRF24L01发送数据
  * @param  data: 数据指针
  * @param  len: 数据长度
  * @retval true:成功 false:失败
  */
bool NRF24L01_Transmit(uint8_t *data, uint8_t len)
{
    uint8_t i;

    NRF_CE_LOW();

    NRF_CSN_LOW();
    BSP_SPI_TransferByte(NRF_CMD_W_TX_PAYLOAD);
    for(i = 0; i < len; i++)
    {
        BSP_SPI_TransferByte(data[i]);
    }
    NRF_CSN_HIGH();

    NRF_CE_HIGH();
    Delay_ms(1);
    NRF_CE_LOW();

    return true;
}
