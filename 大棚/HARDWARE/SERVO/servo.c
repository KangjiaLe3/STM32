/**
  ******************************************************************************
  * @file    servo.c
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   舵机驱动
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "servo.h"
#include "config.h"

/**
  * @brief  舵机初始化
  * @param  None
  * @retval None
  */
void Servo_Init(void)
{
    Servo_AllClose();
}

/**
  * @brief  设置舵机角度
  * @param  servo_num: 舵机编号(1-3)
  * @param  angle: 角度(0-180)
  * @retval None
  */
void Servo_SetAngle(uint8_t servo_num, uint8_t angle)
{
    uint16_t pulse;

    if(angle > 180) angle = 180;

    /* 计算脉冲宽度 */
    pulse = SERVO_MIN_PULSE + (angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE) / 180);

    /* 设置PWM占空比 */
    switch(servo_num)
    {
        case 1:
            TIM_SetCompare2(TIM2, pulse);  /* PB3 - TIM2_CH2 */
            break;
        case 2:
            TIM_SetCompare3(TIM4, pulse);  /* PB8 - TIM4_CH3 */
            break;
        case 3:
            TIM_SetCompare4(TIM4, pulse);  /* PB9 - TIM4_CH4 */
            break;
    }
}

/**
  * @brief  打开所有舵机(90度)
  * @param  None
  * @retval None
  */
void Servo_AllOpen(void)
{
    Servo_SetAngle(1, 90);
    Servo_SetAngle(2, 90);
    Servo_SetAngle(3, 90);
}

/**
  * @brief  关闭所有舵机(0度)
  * @param  None
  * @retval None
  */
void Servo_AllClose(void)
{
    Servo_SetAngle(1, 0);
    Servo_SetAngle(2, 0);
    Servo_SetAngle(3, 0);
}
