# 智能温室大棚项目

## 项目概述
基于两片STM32F103C8T6的智能温室大棚监控系统，通过NRF24L01无线通信实现数据传输。

## 硬件架构

### MCU1 - 传感器控制端
**传感器：**
- TEMT6000 光照传感器 (PA1/ADC1_IN1)
- SCD40 CO2传感器 (PB6/I2C1_SCL, PB7/I2C1_SDA)
- DHT11 温湿度传感器 (PA0/GPIO)
- 土壤湿度传感器 (PA2/ADC1_IN2)

**执行器：**
- 3个舵机 (PA8/TIM1_CH1, PA9/TIM1_CH2, PA10/TIM1_CH3)
- 继电器/水泵 (PB12/GPIO)
- 蜂鸣器 (PB13/GPIO)

**通信：**
- NRF24L01 (PA4/NSS, PA5/SCK, PA6/MISO, PA7/MOSI, PB0/CE, PB1/IRQ)

**按键：**
- 按键1 - 舵机控制 (PB14/GPIO)
- 按键2 - 水泵控制 (PB15/GPIO)

### MCU2 - 显示端
- OLED显示屏 (PB6/I2C1_SCL, PB7/I2C1_SDA)
- NRF24L01 (PA4/NSS, PA5/SCK, PA6/MISO, PA7/MOSI, PB0/CE, PB1/IRQ)

## 功能特性
1. 实时采集温度、湿度、光照、CO2、土壤湿度数据
2. 湿度低于阈值时自动开启水泵和蜂鸣器报警
3. 温度高于阈值时自动开启舵机（通风窗）
4. 手动按键控制舵机和水泵
5. 无线传输数据到显示端
6. OLED实时显示所有传感器数据

## 目录结构
```
smart-greenhouse/
├── MCU1_Sensor/      # 传感器控制端代码
├── MCU2_Display/     # 显示端代码
└── Common/           # 公共配置和协议定义
```
