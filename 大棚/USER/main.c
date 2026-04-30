/**
  ******************************************************************************
  * @file    main.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   主程序
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "protocol.h"
#include "config.h"
#include "bsp_gpio.h"
#include "bsp_adc.h"
#include "bsp_timer.h"
#include "bsp_i2c.h"
#include "bsp_spi.h"
#include "dht11.h"
#include "scd40.h"
#include "temt6000.h"
#include "nrf24l01.h"
#include "servo.h"
#include "relay.h"
#include "control.h"

/* Private variables ---------------------------------------------------------*/
SensorData_t sensor_data = {0};
uint32_t sample_counter = 0;

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
    BSP_ADC_Init();
    BSP_Timer_Init();
    BSP_I2C_Init();
    BSP_SPI_Init();

    /* 传感器和执行器初始化 */
    DHT11_Init();
    SCD40_Init();
    TEMT6000_Init();
    NRF24L01_Init();
    Servo_Init();
    Relay_Init();
    Control_Init();

    /* 等待传感器稳定 */
    Delay_ms(1000);

    /* 主循环 */
    while(1)
    {
        /* 传感器采样（每SAMPLE_INTERVAL毫秒） */
        if(sample_counter >= SAMPLE_INTERVAL)
        {
            /* 读取传感器数据 */
            DHT11_Read(&sensor_data.temperature, &sensor_data.humidity);
            sensor_data.light = TEMT6000_Read();
            sensor_data.co2 = SCD40_Read();
            sensor_data.soil_moisture = BSP_ADC_ReadSoilMoisture();

            /* 自动控制模式 */
            Control_AutoMode(&sensor_data);

            /* 发送数据到MCU2 */
            NRF24L01_Transmit((uint8_t*)&sensor_data, DATA_PACKET_SIZE);

            sample_counter = 0;
        }

        /* 手动控制模式（按键检测） */
        Control_ManualMode(&sensor_data);

        /* 延时1ms */
        Delay_ms(1);
        sample_counter++;
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
