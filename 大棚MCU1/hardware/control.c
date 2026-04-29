/**
  ******************************************************************************
  * @file    control.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   控制逻辑
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "control.h"
#include "servo.h"
#include "relay.h"
#include "bsp_gpio.h"
#include "config.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t key1_pressed = 0;
static uint8_t key2_pressed = 0;
static uint8_t control_mode = MODE_AUTO;

/**
  * @brief  控制逻辑初始化
  * @param  None
  * @retval None
  */
void Control_Init(void)
{
    control_mode = MODE_AUTO;
}

/**
  * @brief  设置控制模式
  * @param  mode: MODE_AUTO或MODE_MANUAL
  * @retval None
  */
void Control_SetMode(uint8_t mode)
{
    control_mode = mode;
}

/**
  * @brief  获取控制模式
  * @param  None
  * @retval 当前控制模式
  */
uint8_t Control_GetMode(void)
{
    return control_mode;
}

/**
  * @brief  自动控制模式
  * @param  data: 传感器数据指针
  * @retval None
  */
void Control_AutoMode(SensorData_t *data)
{
    /* 只有在自动模式下才执行自动控制 */
    if(control_mode != MODE_AUTO)
    {
        return;
    }

    /* 温度过高，开启舵机（通风窗） */
    if(data->temperature > TEMP_HIGH_THRESHOLD)
    {
        Servo_AllOpen();
        data->servo_state = 1;
    }
    else
    {
        Servo_AllClose();
        data->servo_state = 0;
    }

    /* 湿度过低或土壤湿度低，开启水泵和蜂鸣器 */
    if(data->humidity < HUMIDITY_LOW_THRESHOLD ||
       data->soil_moisture < SOIL_MOISTURE_LOW)
    {
        Relay_On();
        Buzzer_On();
        data->relay_state = 1;
        data->buzzer_state = 1;
    }
    else
    {
        Relay_Off();
        Buzzer_Off();
        data->relay_state = 0;
        data->buzzer_state = 0;
    }

    data->control_mode = MODE_AUTO;
}

/**
  * @brief  手动控制模式
  * @param  data: 传感器数据指针
  * @retval None
  */
void Control_ManualMode(SensorData_t *data)
{
    /* 按键1控制舵机并切换到手动模式 */
    if(GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == RESET)
    {
        if(!key1_pressed)
        {
            key1_pressed = 1;
            control_mode = MODE_MANUAL;

            if(data->servo_state)
            {
                Servo_AllClose();
                data->servo_state = 0;
            }
            else
            {
                Servo_AllOpen();
                data->servo_state = 1;
            }
        }
    }
    else
    {
        key1_pressed = 0;
    }

    /* 按键2控制水泵并切换到手动模式 */
    if(GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == RESET)
    {
        if(!key2_pressed)
        {
            key2_pressed = 1;
            control_mode = MODE_MANUAL;

            if(data->relay_state)
            {
                Relay_Off();
                Buzzer_Off();
                data->relay_state = 0;
                data->buzzer_state = 0;
            }
            else
            {
                Relay_On();
                data->relay_state = 1;
            }
        }
    }
    else
    {
        key2_pressed = 0;
    }

    data->control_mode = control_mode;
}
