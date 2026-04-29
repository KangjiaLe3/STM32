/**
  ******************************************************************************
  * @file    dht11.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   DHT11温湿度传感器驱动
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "dht11.h"
#include "bsp_gpio.h"

/* 外部延时函数 */
extern void Delay_ms(uint32_t nTime);

/* Private functions ---------------------------------------------------------*/
static void delay_us(uint32_t us)
{
    uint32_t ticks = us * 72 / 4;
    while(ticks--);
}

static void DHT11_SetOutput(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
}

static void DHT11_SetInput(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DHT11_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  DHT11初始化
  * @param  None
  * @retval None
  */
void DHT11_Init(void)
{
    DHT11_SetOutput();
    GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
}

/**
  * @brief  读取DHT11温湿度数据
  * @param  temperature: 温度指针
  * @param  humidity: 湿度指针
  * @retval true:成功 false:失败
  */
bool DHT11_Read(float *temperature, float *humidity)
{
    uint8_t data[5] = {0};
    uint32_t timeout;
    uint8_t i;

    /* 发送起始信号 */
    DHT11_SetOutput();
    GPIO_ResetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
    Delay_ms(18);
    GPIO_SetBits(DHT11_GPIO_PORT, DHT11_GPIO_PIN);
    delay_us(30);
    DHT11_SetInput();

    /* 等待DHT11响应 */
    timeout = 0;
    while(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && timeout < 10000)
    {
        timeout++;
        delay_us(1);
    }
    if(timeout >= 10000) return false;

    timeout = 0;
    while(!GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && timeout < 10000)
    {
        timeout++;
        delay_us(1);
    }
    if(timeout >= 10000) return false;

    timeout = 0;
    while(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && timeout < 10000)
    {
        timeout++;
        delay_us(1);
    }
    if(timeout >= 10000) return false;

    /* 读取40位数据 */
    for(i = 0; i < 40; i++)
    {
        timeout = 0;
        while(!GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && timeout < 10000)
        {
            timeout++;
            delay_us(1);
        }
        if(timeout >= 10000) return false;

        delay_us(30);

        if(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN))
        {
            data[i/8] |= (1 << (7 - i%8));
        }

        timeout = 0;
        while(GPIO_ReadInputDataBit(DHT11_GPIO_PORT, DHT11_GPIO_PIN) && timeout < 10000)
        {
            timeout++;
            delay_us(1);
        }
        if(timeout >= 10000) return false;
    }

    /* 校验和验证 */
    if(data[4] != ((data[0] + data[1] + data[2] + data[3]) & 0xFF))
    {
        return false;
    }

    /* 解析数据 */
    *humidity = data[0] + data[1] * 0.1f;
    *temperature = data[2] + data[3] * 0.1f;

    return true;
}
