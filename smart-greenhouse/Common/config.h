#ifndef __CONFIG_H
#define __CONFIG_H

// 温湿度阈值
#define TEMP_HIGH_THRESHOLD     30.0f   // 温度高阈值 (°C)
#define HUMIDITY_LOW_THRESHOLD  40.0f   // 湿度低阈值 (%)
#define SOIL_MOISTURE_LOW       1500    // 土壤湿度低阈值 (ADC值)

// NRF24L01配置
#define NRF_CHANNEL     76
#define NRF_ADDRESS     "GHOUS"

// 舵机PWM配置
#define SERVO_MIN_PULSE 500     // 0度对应的脉冲宽度(us)
#define SERVO_MAX_PULSE 2500    // 180度对应的脉冲宽度(us)

// 采样间隔
#define SAMPLE_INTERVAL 2000    // 传感器采样间隔(ms)

#endif
