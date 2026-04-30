# 智能温室大棚项目 - Keil5完整配置指南

## 📋 项目说明

这是**MCU1（传感器控制端）**的完整代码，基于：
- **开发工具**: Keil MDK 5
- **芯片**: STM32F103C8T6
- **标准库**: STM32F10x_StdPeriph_Driver
- **开发板**: KPZ32

## 📁 完整目录结构

```
greenhouse-kpz32/
├── USER/                          # 用户代码
│   ├── main.c                     # 主程序
│   ├── main.h                     # 主程序头文件
│   ├── protocol.h                 # 通信协议定义
│   ├── config.h                   # 系统配置参数
│   ├── stm32f10x_conf.h          # 标准库配置（需要用户提供）
│   └── stm32f10x_it.c/h          # 中断服务函数（需要用户提供）
│
├── BSP/                           # 板级支持包
│   ├── bsp_gpio.c/h              # GPIO配置
│   ├── bsp_adc.c/h               # ADC配置
│   ├── bsp_timer.c/h             # 定时器配置（舵机PWM）
│   ├── bsp_i2c.c/h               # 软件I2C
│   └── bsp_spi.c/h               # SPI配置
│
├── HARDWARE/                      # 硬件驱动
│   ├── DHT11/
│   │   ├── dht11.c
│   │   └── dht11.h
│   ├── SCD40/
│   │   ├── scd40.c
│   │   └── scd40.h
│   ├── TEMT6000/
│   │   ├── temt6000.c
│   │   └── temt6000.h
│   ├── NRF24L01/
│   │   ├── nrf24l01.c
│   │   └── nrf24l01.h
│   ├── SERVO/
│   │   ├── servo.c
│   │   └── servo.h
│   ├── RELAY/
│   │   ├── relay.c
│   │   └── relay.h
│   └── CONTROL/
│       ├── control.c
│       └── control.h
│
├── STM32F10x_StdPeriph_Driver/   # 标准库（需要用户提供）
│   ├── inc/                       # 标准库头文件
│   └── src/                       # 标准库源文件
│
├── CMSIS/                         # CMSIS核心文件（需要用户提供）
│   ├── CM3/
│   │   ├── CoreSupport/
│   │   └── DeviceSupport/ST/STM32F10x/
│   └── startup/
│       └── startup_stm32f10x_md.s
│
└── OUTPUT/                        # 编译输出目录
```

## 🔧 Keil5项目配置

### 1. C/C++ 选项卡配置

**Include Paths（头文件路径）：**
```
.\USER
.\BSP
.\HARDWARE\DHT11
.\HARDWARE\SCD40
.\HARDWARE\TEMT6000
.\HARDWARE\NRF24L01
.\HARDWARE\SERVO
.\HARDWARE\RELAY
.\HARDWARE\CONTROL
.\STM32F10x_StdPeriph_Driver\inc
.\CMSIS\CM3\CoreSupport
.\CMSIS\CM3\DeviceSupport\ST\STM32F10x
```

**Preprocessor Symbols（预处理器定义）：**
```
STM32F10X_MD
USE_STDPERIPH_DRIVER
```

### 2. 文件分组（Groups）

在Keil5项目中创建以下分组：

```
Project
├── USER
│   ├── main.c
│   ├── stm32f10x_it.c
│   └── system_stm32f10x.c
│
├── BSP
│   ├── bsp_gpio.c
│   ├── bsp_adc.c
│   ├── bsp_timer.c
│   ├── bsp_i2c.c
│   └── bsp_spi.c
│
├── HARDWARE
│   ├── dht11.c
│   ├── scd40.c
│   ├── temt6000.c
│   ├── nrf24l01.c
│   ├── servo.c
│   ├── relay.c
│   └── control.c
│
├── STM32F10x_StdPeriph_Driver
│   ├── stm32f10x_gpio.c
│   ├── stm32f10x_rcc.c
│   ├── stm32f10x_adc.c
│   ├── stm32f10x_tim.c
│   ├── stm32f10x_spi.c
│   ├── stm32f10x_flash.c
│   └── misc.c
│
├── CMSIS
│   ├── core_cm3.c
│   └── system_stm32f10x.c
│
└── STARTUP
    └── startup_stm32f10x_md.s
```

### 3. Target选项卡配置

**Device**: STM32F103C8
**Crystal**: 8.0 MHz（外部晶振）

### 4. Debug选项卡配置

**Use**: ST-Link Debugger
**Settings**: 
- Port: SW (Serial Wire)
- Max Clock: 4 MHz

## ⚠️ 用户需要提供的文件

### 1. 标准库文件
从ST官网下载STM32F10x标准库，需要以下文件：

**标准库源文件（STM32F10x_StdPeriph_Driver/src/）：**
- stm32f10x_gpio.c
- stm32f10x_rcc.c
- stm32f10x_adc.c
- stm32f10x_tim.c
- stm32f10x_spi.c
- stm32f10x_flash.c
- misc.c

**标准库头文件（STM32F10x_StdPeriph_Driver/inc/）：**
- stm32f10x_gpio.h
- stm32f10x_rcc.h
- stm32f10x_adc.h
- stm32f10x_tim.h
- stm32f10x_spi.h
- stm32f10x_flash.h
- misc.h

### 2. CMSIS文件

**CMSIS核心文件（CMSIS/CM3/CoreSupport/）：**
- core_cm3.c
- core_cm3.h

**设备支持文件（CMSIS/CM3/DeviceSupport/ST/STM32F10x/）：**
- stm32f10x.h
- system_stm32f10x.c
- system_stm32f10x.h

**启动文件（CMSIS/startup/）：**
- startup_stm32f10x_md.s

### 3. 用户配置文件

**USER/stm32f10x_conf.h：**
```c
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* 包含需要使用的标准库头文件 */
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_flash.h"
#include "misc.h"

/* 断言宏定义 */
#ifdef  USE_FULL_ASSERT
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif

#endif /* __STM32F10x_CONF_H */
```

### 4. Delay_ms()函数

**USER/delay.c：**
```c
#include "stm32f10x.h"

static __IO uint32_t TimingDelay;

void SysTick_Handler(void)
{
    if(TimingDelay != 0x00)
    {
        TimingDelay--;
    }
}

void Delay_ms(uint32_t nTime)
{
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

void Delay_Init(void)
{
    /* SysTick配置为1ms中断 */
    if(SysTick_Config(SystemCoreClock / 1000))
    {
        while(1);
    }
}
```

**在main.c的main()函数开头调用：**
```c
int main(void)
{
    SystemClock_Config();
    Delay_Init();  // 初始化延时函数
    
    // ... 其他初始化
}
```

## ✅ 编译前检查清单

- [ ] 所有标准库文件已添加到项目
- [ ] Include Paths已正确配置
- [ ] 预处理器定义已添加（STM32F10X_MD, USE_STDPERIPH_DRIVER）
- [ ] startup_stm32f10x_md.s已添加到项目
- [ ] stm32f10x_conf.h已创建
- [ ] Delay_ms()函数已实现
- [ ] SysTick_Handler()已在stm32f10x_it.c中声明
- [ ] 所有文件分组已创建

## 🎯 引脚分配总结

| 功能 | 引脚 | 配置 |
|------|------|------|
| DHT11 | PA1 | GPIO |
| TEMT6000 | PA0 | ADC1_IN0 |
| 土壤湿度 | PA2 | ADC1_IN2 |
| SCD40 SDA | PB6 | 软件I2C |
| SCD40 SCL | PB7 | 软件I2C |
| 舵机1 | PB3 | TIM2_CH2 |
| 舵机2 | PB8 | TIM4_CH3 |
| 舵机3 | PB9 | TIM4_CH4 |
| 继电器 | PB4 | GPIO |
| 蜂鸣器 | PB5 | GPIO |
| 按键1 | PA8 | GPIO_IPU |
| 按键2 | PA11 | GPIO_IPU |
| NRF CE | PB0 | GPIO |
| NRF CSN | PA4 | GPIO |
| NRF SCK | PA5 | SPI1_SCK |
| NRF MISO | PA6 | SPI1_MISO |
| NRF MOSI | PA7 | SPI1_MOSI |
| NRF IRQ | PB1 | GPIO_IPU |

## 📝 编译步骤

1. 打开Keil5，创建新项目
2. 选择芯片：STM32F103C8
3. 添加所有源文件到对应分组
4. 配置Include Paths和预处理器定义
5. 点击Build（F7）编译
6. 连接ST-Link
7. 点击Download（F8）下载到芯片

## 🔍 常见编译错误解决

### 错误1: "cannot open source input file stm32f10x.h"
**解决**: 检查Include Paths是否包含CMSIS路径

### 错误2: "undefined reference to Delay_ms"
**解决**: 确保delay.c已添加到项目并实现了Delay_ms()

### 错误3: "undefined symbol SysTick_Handler"
**解决**: 在stm32f10x_it.c中添加SysTick_Handler()函数

### 错误4: 按键不响应
**解决**: 确保按键配置为GPIO_Mode_IPU（上拉输入）

### 错误5: DHT11读取失败
**解决**: 检查超时阈值是否足够大（10000），delay_us()是否正确

## 🎉 项目完成状态

✅ 所有MCU1代码文件已创建完成
✅ 基于Keil5和STM32标准库
✅ 所有引脚冲突已解决
✅ 控制逻辑已修正（手动/自动模式）
✅ 结构体对齐已添加（#pragma pack(1)）
✅ 按键配置为上拉输入
✅ DHT11超时机制已修正

**总文件数**: 30+个文件
**代码行数**: 约2500+行
**适配硬件**: KPZ32开发板 + STM32F103C8T6

---

**注意**: 这是MCU1的完整代码。MCU2（显示端）的代码需要另外创建。
