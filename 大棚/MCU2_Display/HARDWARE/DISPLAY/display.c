/**
  ******************************************************************************
  * @file    display.c
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   显示逻辑
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "display.h"
#include "oled.h"
#include <stdio.h>
#include <string.h>

/**
  * @brief  显示初始化
  * @param  None
  * @retval None
  */
void Display_Init(void)
{
    /* OLED已在main中初始化 */
}

/**
  * @brief  更新显示内容
  * @param  data: 传感器数据指针
  * @retval None
  */
void Display_Update(SensorData_t *data)
{
    char buf[32];

    /* 清屏 */
    OLED_Clear();

    /* 显示标题 */
    OLED_ShowString(0, 0, "Smart Greenhouse");

    /* 显示温度 */
    sprintf(buf, "Temp: %.1fC", data->temperature);
    OLED_ShowString(0, 2, buf);

    /* 显示湿度 */
    sprintf(buf, "Humi: %.1f%%", data->humidity);
    OLED_ShowString(0, 3, buf);

    /* 显示光照 */
    sprintf(buf, "Light: %d", data->light);
    OLED_ShowString(0, 4, buf);

    /* 显示CO2 */
    sprintf(buf, "CO2: %dppm", data->co2);
    OLED_ShowString(0, 5, buf);

    /* 显示土壤湿度 */
    sprintf(buf, "Soil: %d", data->soil_moisture);
    OLED_ShowString(0, 6, buf);

    /* 显示状态 */
    sprintf(buf, "R:%d S:%d B:%d M:%d",
            data->relay_state,
            data->servo_state,
            data->buzzer_state,
            data->control_mode);
    OLED_ShowString(0, 7, buf);
}
