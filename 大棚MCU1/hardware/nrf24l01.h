/**
  ******************************************************************************
  * @file    nrf24l01.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   NRF24L01无线模块驱动头文件
  ******************************************************************************
  */

#ifndef __NRF24L01_H
#define __NRF24L01_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdbool.h>

/* NRF24L01寄存器地址 */
#define NRF_CONFIG      0x00
#define NRF_EN_AA       0x01
#define NRF_EN_RXADDR   0x02
#define NRF_SETUP_AW    0x03
#define NRF_SETUP_RETR  0x04
#define NRF_RF_CH       0x05
#define NRF_RF_SETUP    0x06
#define NRF_STATUS      0x07
#define NRF_TX_ADDR     0x10
#define NRF_RX_ADDR_P0  0x0A
#define NRF_RX_PW_P0    0x11

/* NRF24L01命令 */
#define NRF_CMD_W_TX_PAYLOAD    0xA0
#define NRF_CMD_FLUSH_TX        0xE1

/* Exported functions --------------------------------------------------------*/
void NRF24L01_Init(void);
bool NRF24L01_Transmit(uint8_t *data, uint8_t len);

#endif /* __NRF24L01_H */
