# KPZ32引脚配置对比

## 原始设计 vs KPZ32适配版本

### 传感器接口

| 传感器 | 原始引脚 | KPZ32引脚 | 说明 |
|--------|----------|-----------|------|
| DHT11温湿度 | PA0 | **PA1** | 使用传感器S1接口 |
| TEMT6000光照 | PA1 (ADC1_IN1) | **PA0 (ADC1_IN0)** | 使用传感器S1接口 |
| 土壤湿度 | PA2 (ADC1_IN2) | **PA2 (ADC1_IN2)** | 使用传感器S3接口，保持不变 |
| SCD40 CO2 | PB6/PB7 (I2C1) | **PA15/PA14 (软件I2C)** | 使用手柄接口引脚 |

### PWM舵机接口

| 舵机 | 原始引脚 | 原始定时器 | KPZ32引脚 | KPZ32定时器 |
|------|----------|------------|-----------|-------------|
| 舵机1 | PA8 | TIM1_CH1 | **PB3** | **TIM2_CH2** |
| 舵机2 | PA9 | TIM1_CH2 | **PB8** | **TIM4_CH3** |
| 舵机3 | PA10 | TIM1_CH3 | **PB9** | **TIM4_CH4** |

### 执行器

| 设备 | 原始引脚 | KPZ32引脚 | 说明 |
|------|----------|-----------|------|
| 继电器/水泵 | PB12 | **PB5** | GPIO输出 |
| 蜂鸣器 | PB13 | **PB2** | GPIO输出 |

### 按键

| 按键 | 原始引脚 | KPZ32引脚 | 功能 |
|------|----------|-----------|------|
| 按键1 | PB14 | **PA8** | 舵机控制 |
| 按键2 | PB15 | **PA11** | 水泵控制 |

### 通信接口

| 模块 | 原始引脚 | KPZ32引脚 | 说明 |
|------|----------|-----------|------|
| NRF24L01 CE | PB0 | **PA4** | 待确认 |
| NRF24L01 IRQ | PB1 | **PB1** | 待确认 |
| NRF24L01 SPI | PA4-PA7 | **待配置** | 需根据实际连接确定 |

## 主要变更说明

### 1. 舵机PWM定时器变更
- **原因**：KPZ32的PWM舵机接口使用PB3/PB8/PB9引脚
- **影响**：需要从TIM1切换到TIM2和TIM4
- **代码变更**：
  - `tim.c`: 重新配置TIM2_CH2, TIM4_CH3, TIM4_CH4
  - `servo.c`: 更新CCR寄存器映射

### 2. I2C接口变更
- **原因**：KPZ32的I2C引脚被OLED占用，需要使用其他引脚
- **解决方案**：使用软件I2C，利用手柄接口的PA15(DAT)和PA14(CMD)
- **代码变更**：
  - `i2c.c`: 实现软件I2C位操作
  - `scd40.c`: 适配软件I2C接口

### 3. DHT11引脚变更
- **原因**：PA0被TEMT6000光照传感器占用（需要ADC）
- **解决方案**：将DHT11移至PA1
- **代码变更**：
  - `gpio.h`: 更新DHT11_PIN定义
  - `dht11.c`: 更新引脚操作

### 4. 按键引脚变更
- **原因**：KPZ32板载按键位于PA8和PA11
- **优势**：直接使用板载按键，无需外接
- **代码变更**：
  - `gpio.h`: 更新KEY1_PIN和KEY2_PIN定义

### 5. 执行器引脚变更
- **原因**：原引脚PB12/PB13可能被其他功能占用
- **解决方案**：使用空闲的PB5和PB2
- **代码变更**：
  - `gpio.h`: 更新RELAY_PIN和BUZZER_PIN定义

## KPZ32开发板特点

根据引脚分布图，KPZ32提供：
- **6个传感器接口** (S1-S6)：每个提供5V/GND和信号引脚
- **6个PWM舵机接口**：PB3, PB8, PB9, PB6, PB7, PB4
- **2个板载按键**：PA8, PA11
- **串口接口**：TX3(PB10), RX3(PB11)
- **蓝牙接口**：TX3(PB10), RX3(PB11)
- **手柄接口**：PA15(DAT), PA14(CMD), PA12(CLT), PA13(ATT)
- **红外接口**：PA8

## 代码文件变更清单

### 已更新的文件
- ✅ `Common/config.h` - 配置参数
- ✅ `Common/protocol.h` - 通信协议
- ✅ `MCU1_Sensor/Core/Inc/gpio.h` - GPIO引脚定义
- ✅ `MCU1_Sensor/Core/Inc/adc.h` - ADC通道定义
- ✅ `MCU1_Sensor/Core/Inc/tim.h` - 定时器配置
- ✅ `MCU1_Sensor/Core/Inc/i2c.h` - 软件I2C接口
- ✅ `MCU1_Sensor/Core/Src/gpio.c` - GPIO初始化
- ✅ `MCU1_Sensor/Core/Src/adc.c` - ADC初始化
- ✅ `MCU1_Sensor/Core/Src/tim.c` - 定时器初始化
- ✅ `MCU1_Sensor/Core/Src/i2c.c` - 软件I2C实现
- ✅ `MCU1_Sensor/Drivers/Servo/servo.h` - 舵机驱动头文件
- ✅ `MCU1_Sensor/Drivers/Servo/servo.c` - 舵机驱动实现

### 待创建的文件
- ⏳ `MCU1_Sensor/Core/Src/main.c` - 主程序
- ⏳ `MCU1_Sensor/Drivers/DHT11/*` - DHT11驱动
- ⏳ `MCU1_Sensor/Drivers/SCD40/*` - SCD40驱动
- ⏳ `MCU1_Sensor/Drivers/TEMT6000/*` - TEMT6000驱动
- ⏳ `MCU1_Sensor/Drivers/Relay/*` - 继电器驱动
- ⏳ `MCU1_Sensor/App/control.*` - 控制逻辑

## 测试建议

1. **单独测试每个传感器**
   - DHT11温湿度读取
   - TEMT6000光照ADC读取
   - 土壤湿度ADC读取
   - SCD40 CO2读取（软件I2C）

2. **测试执行器**
   - 舵机角度控制（0-180度）
   - 继电器开关
   - 蜂鸣器开关

3. **测试按键**
   - 按键1触发舵机
   - 按键2触发水泵

4. **集成测试**
   - 自动控制逻辑
   - 数据采集和显示
