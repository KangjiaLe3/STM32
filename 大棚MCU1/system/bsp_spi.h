/**
  ******************************************************************************
  * @file    bsp_spi.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   SPI板级支持包头文件
  ******************************************************************************
  */

#ifndef __BSP_SPI_H
#define __BSP_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported functions --------------------------------------------------------*/
void BSP_SPI_Init(void);
uint8_t BSP_SPI_TransferByte(uint8_t data);

#endif /* __BSP_SPI_H */
