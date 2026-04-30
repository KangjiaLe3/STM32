/**
  ******************************************************************************
  * @file    main.c
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   MCU2主程序（显示端）
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "protocol.h"
#include "bsp_gpio.h"
#include "bsp_i2c.h"
#include "bsp_spi.h"
#include "nrf24l01.h"
#include "oled.h"
#include "display.h"

/* Private variables ---------------------------------------------------------*/
SensorData_t sensor_data = {0};

/**
  * @brief  主函数
  * @param  None
  * @retval None
  */
int main(void)
{
    /* 系统时钟配置 */
    SystemClock_Config();

    /* 外设初始化 */
    BSP_GPIO_Init();
    BSP_I2C_Init();
    BSP_SPI_Init();

    /* 硬件模块初始化 */
    OLED_Init();
    NRF24L01_Init();
    Display_Init();

    /* 等待系统稳定 */
    Delay_ms(1000);

    /* 显示欢迎信息 */
    OLED_Clear();
    OLED_ShowString(0, 0, "SMART GREENHOUS");
    OLED_ShowString(0, 2, "WATING DATA...");
    Delay_ms(2000);

    /* 主循环 */
    while(1)
    {
        /* 接收数据 */
        if(NRF24L01_Receive((uint8_t*)&sensor_data, DATA_PACKET_SIZE))
        {
            /* 更新显示 */
            Display_Update(&sensor_data);
        }

        Delay_ms(10);
    }
}

/**
  * @brief  系统时钟配置为72MHz
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{
    ErrorStatus HSEStartUpStatus;

    /* 使能HSE */
    RCC_HSEConfig(RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if(HSEStartUpStatus == SUCCESS)
    {
        /* 使能Prefetch Buffer */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        /* Flash 2 wait state */
        FLASH_SetLatency(FLASH_Latency_2);

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);

        /* PCLK1 = HCLK/2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);

        /* PLLCLK = 8MHz * 9 = 72MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

        /* 使能PLL */
        RCC_PLLCmd(ENABLE);

        /* 等待PLL就绪 */
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

        /* 选择PLL作为系统时钟 */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* 等待PLL被选为系统时钟 */
        while(RCC_GetSYSCLKSource() != 0x08);
    }
}
