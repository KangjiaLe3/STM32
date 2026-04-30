/**
  ******************************************************************************
  * @file    servo.h
  * @author  Smart Greenhouse Project
  * @version V1.0
  * @date    2024
  * @brief   舵机驱动头文件
  ******************************************************************************
  */

#ifndef __SERVO_H
#define __SERVO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported functions --------------------------------------------------------*/
void Servo_Init(void);
void Servo_SetAngle(uint8_t servo_num, uint8_t angle);
void Servo_AllOpen(void);
void Servo_AllClose(void);

#endif /* __SERVO_H */
