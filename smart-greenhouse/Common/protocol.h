#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <stdint.h>

// 数据包结构定义
typedef struct {
    float temperature;      // 温度 (°C)
    float humidity;         // 湿度 (%)
    uint16_t light;         // 光照强度 (0-4095)
    uint16_t co2;           // CO2浓度 (ppm)
    uint16_t soil_moisture; // 土壤湿度 (0-4095)
    uint8_t relay_state;    // 继电器状态 (0/1)
    uint8_t servo_state;    // 舵机状态 (0/1)
    uint8_t buzzer_state;   // 蜂鸣器状态 (0/1)
} SensorData_t;

#define DATA_PACKET_SIZE sizeof(SensorData_t)

#endif
