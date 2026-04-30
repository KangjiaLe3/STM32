/**
  ******************************************************************************
  * @file    protocol.h
  * @author  Smart Greenhouse Project - MCU2
  * @version V1.0
  * @date    2024
  * @brief   通信协议定义（与MCU1共用）
  ******************************************************************************
  */

#ifndef __PROTOCOL_H
#define __PROTOCOL_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* 强制1字节对齐，确保跨MCU通信时结构体布局一致 */
#pragma pack(1)

/* 数据包结构定义 */
typedef struct
{
    float temperature;      /* 温度 (°C) */
    float humidity;         /* 湿度 (%) */
    uint16_t light;         /* 光照强度 (0-4095) */
    uint16_t co2;           /* CO2浓度 (ppm) */
    uint16_t soil_moisture; /* 土壤湿度 (0-4095) */
    uint8_t relay_state;    /* 继电器状态 (0/1) */
    uint8_t servo_state;    /* 舵机状态 (0/1) */
    uint8_t buzzer_state;   /* 蜂鸣器状态 (0/1) */
    uint8_t control_mode;   /* 控制模式 (0=自动, 1=手动) */
} SensorData_t;

#pragma pack()

/* 数据包大小 */
#define DATA_PACKET_SIZE sizeof(SensorData_t)

/* 控制模式定义 */
#define MODE_AUTO   0
#define MODE_MANUAL 1

#endif /* __PROTOCOL_H */
