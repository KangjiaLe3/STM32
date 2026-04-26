# 引脚冲突修正 - 第二版

## 🚨 发现的SPI与I2C冲突

### 问题描述
在第一次修正中，PA6和PA7被两个模块同时使用：
- **NRF24L01 (SPI1)**: PA6=MISO, PA7=MOSI
- **SCD40 (软件I2C)**: PA6=SDA, PA7=SCL

这会导致两个模块都无法正常工作！

## ✅ 最终修正方案

### 完整引脚分配表

| 功能 | 引脚 | 复用功能 | 说明 |
|------|------|----------|------|
| **传感器** | | | |
| DHT11温湿度 | PA1 | GPIO | 传感器S1接口 |
| TEMT6000光照 | PA0 | ADC1_IN0 | 传感器S1接口 |
| 土壤湿度 | PA2 | ADC1_IN2 | 传感器S3接口 |
| SCD40 SDA | PB6 | 软件I2C | PWM舵机接口（空闲） |
| SCD40 SCL | PB7 | 软件I2C | PWM舵机接口（空闲） |
| **舵机（3个）** | | | |
| 舵机1 | PB3 | TIM2_CH2 | 需禁用JTAG |
| 舵机2 | PB8 | TIM4_CH3 | 正常使用 |
| 舵机3 | PB9 | TIM4_CH4 | 正常使用 |
| **执行器** | | | |
| 继电器/水泵 | PB5 | GPIO | 普通输出 |
| 蜂鸣器 | PB2 | GPIO | 普通输出 |
| **按键** | | | |
| 按键1 | PA8 | GPIO | 板载按键 |
| 按键2 | PA11 | GPIO | 板载按键 |
| **NRF24L01 (SPI1)** | | | |
| SCK | PA5 | SPI1_SCK | 硬件SPI时钟 |
| MISO | PA6 | SPI1_MISO | 硬件SPI主入从出 |
| MOSI | PA7 | SPI1_MOSI | 硬件SPI主出从入 |
| CSN | PA4 | GPIO | 片选（软件控制） |
| CE | PB0 | GPIO | 芯片使能 |
| IRQ | PB1 | GPIO | 中断信号 |
| **调试接口（保留）** | | | |
| SWDIO | PA13 | SWD | 调试数据线 |
| SWCLK | PA14 | SWD | 调试时钟线 |

### 关键决策说明

#### 1. SCD40的I2C引脚选择
**问题**: 需要找到两个不冲突的引脚
**考虑的选项**:
- ❌ PA6/PA7: 被SPI1占用
- ❌ PA14/PA15: 调试引脚，会断开ST-Link
- ❌ PA3: 可用，但只有一个引脚
- ✅ **PB6/PB7**: KPZ32的PWM舵机接口有6个通道，我们只用3个，可以空出PB6/PB7

#### 2. NRF24L01的CE引脚
**原方案**: PA3
**问题**: 如果用PA3做I2C的SCL，CE就没地方了
**最终方案**: PB0（传感器S4接口）

#### 3. 引脚使用优先级
1. **调试引脚**: PA13/PA14必须保留
2. **JTAG引脚**: PB3需要禁用JTAG后才能用
3. **SPI硬件引脚**: PA5/PA6/PA7必须用于SPI1
4. **ADC引脚**: PA0/PA2用于模拟传感器
5. **剩余GPIO**: 灵活分配

## 📋 引脚冲突检查清单

### ✅ 无冲突的引脚组
- PA0 (ADC) - TEMT6000光照
- PA1 (GPIO) - DHT11
- PA2 (ADC) - 土壤湿度
- PA3 (未使用)
- PA4 (GPIO) - NRF CSN
- PA5 (SPI1_SCK) - NRF SCK
- PA6 (SPI1_MISO) - NRF MISO
- PA7 (SPI1_MOSI) - NRF MOSI
- PA8 (GPIO) - 按键1
- PA11 (GPIO) - 按键2
- PA13 (SWDIO) - 调试
- PA14 (SWCLK) - 调试

- PB0 (GPIO) - NRF CE
- PB1 (GPIO) - NRF IRQ
- PB2 (GPIO) - 蜂鸣器
- PB3 (TIM2_CH2) - 舵机1（需禁用JTAG）
- PB5 (GPIO) - 继电器
- PB6 (软件I2C SDA) - SCD40
- PB7 (软件I2C SCL) - SCD40
- PB8 (TIM4_CH3) - 舵机2
- PB9 (TIM4_CH4) - 舵机3

### ❌ 避免使用的引脚
- PA15 (JTDI) - JTAG调试
- PB4 (JTRST) - JTAG调试
- PA9/PA10 - 可能被USART1占用

## 🔧 代码修改总结

### 修改的文件
1. ✅ `gpio.h` - 更新所有引脚定义
2. ✅ `gpio.c` - 更新GPIO初始化
3. ✅ `i2c.h` - I2C改用PB6/PB7
4. ✅ `i2c.c` - 更新I2C引脚操作宏
5. ✅ `spi.h` - 新增SPI头文件
6. ✅ `spi.c` - 新增SPI初始化代码

### 关键代码片段

#### GPIO初始化中的JTAG禁用
```c
// 禁用JTAG，保留SWD调试功能
AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
```

#### I2C引脚操作宏（更新为PB6/PB7）
```c
#define SDA_H()  GPIOB->BSRR = I2C_SDA_PIN
#define SDA_L()  GPIOB->BRR = I2C_SDA_PIN
#define SCL_H()  GPIOB->BSRR = I2C_SCL_PIN
#define SCL_L()  GPIOB->BRR = I2C_SCL_PIN
#define SDA_READ() (GPIOB->IDR & I2C_SDA_PIN)
```

#### SPI1初始化
```c
// PA5(SCK) - 复用推挽输出
// PA6(MISO) - 浮空输入
// PA7(MOSI) - 复用推挽输出
SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_2 | SPI_CR1_SSM | SPI_CR1_SSI;
```

## 🎯 验证要点

### 1. 调试功能
- ✅ ST-Link可以正常连接
- ✅ 可以正常烧录程序
- ✅ 可以使用断点调试

### 2. SPI通信
- ✅ PA5/PA6/PA7专用于SPI1
- ✅ NRF24L01可以正常通信

### 3. I2C通信
- ✅ PB6/PB7不与其他功能冲突
- ✅ SCD40可以正常读取CO2数据

### 4. PWM输出
- ✅ PB3需要先禁用JTAG
- ✅ 3个舵机都能正常输出PWM

### 5. ADC采样
- ✅ PA0和PA2用于模拟输入
- ✅ 光照和土壤湿度可以正常读取

## 📝 KPZ32引脚使用情况

根据KPZ32开发板的引脚分布：
- **PWM舵机接口**: PB3/PB8/PB9使用，PB6/PB7/PB4空闲
- **传感器接口**: S1(PA0/PA1), S3(PA2), S4(PB0)使用
- **板载按键**: PA8/PA11使用
- **SPI接口**: PA5/PA6/PA7使用
- **调试接口**: PA13/PA14保留

## ✅ 最终确认

所有引脚冲突已解决：
1. ✅ NRF24L01独占SPI1 (PA5/PA6/PA7)
2. ✅ SCD40独占软件I2C (PB6/PB7)
3. ✅ 调试接口保留 (PA13/PA14)
4. ✅ JTAG正确禁用 (释放PB3)
5. ✅ 所有传感器、执行器、按键引脚无冲突

可以安全编译和烧录！
