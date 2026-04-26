# 引脚配置修正说明

## 🚨 发现的严重问题

### 1. NRF24L01引脚冲突
**问题**: CE和CSN都分配给了PA4
**后果**: NRF24L01无法正常工作
**修正**: 
- CE: PA3
- CSN: PA4

### 2. 调试引脚冲突
**问题**: 使用了PA14(SWCLK)作为I2C的SCL
**后果**: 
- ST-Link调试器会立即断开连接
- 无法再次烧录程序
- 出现"No target connected"错误

**修正**: 改用PA6(SDA)和PA7(SCL)

### 3. JTAG引脚未重映射
**问题**: 直接使用PB3(JTDO)和PA15(JTDI)作为普通GPIO
**后果**:
- PB3的舵机1无反应
- PA15的I2C无法工作

**修正**: 在GPIO初始化时禁用JTAG，保留SWD调试功能

## ✅ 修正后的引脚分配

### 传感器接口
| 传感器 | 引脚 | 说明 |
|--------|------|------|
| DHT11温湿度 | PA1 | 传感器S1接口 |
| TEMT6000光照 | PA0 (ADC) | 传感器S1接口 |
| 土壤湿度 | PA2 (ADC) | 传感器S3接口 |
| SCD40 CO2 | PA6(SDA), PA7(SCL) | 软件I2C，传感器S5/S6接口 |

### PWM舵机接口
| 舵机 | 引脚 | 定时器 | 注意事项 |
|------|------|--------|----------|
| 舵机1 | PB3 | TIM2_CH2 | 需禁用JTAG |
| 舵机2 | PB8 | TIM4_CH3 | 正常使用 |
| 舵机3 | PB9 | TIM4_CH4 | 正常使用 |

### 执行器
| 设备 | 引脚 |
|------|------|
| 继电器/水泵 | PB5 |
| 蜂鸣器 | PB2 |

### 按键
| 按键 | 引脚 | 功能 |
|------|------|------|
| 按键1 | PA8 | 舵机控制 |
| 按键2 | PA11 | 水泵控制 |

### NRF24L01通信
| 信号 | 引脚 | 说明 |
|------|------|------|
| CE | PA3 | 芯片使能 |
| CSN | PA4 | 片选信号 |
| SCK | PA5 | SPI时钟 |
| MISO | PA6 | SPI主入从出 |
| MOSI | PA7 | SPI主出从入 |
| IRQ | PB1 | 中断信号 |

### 调试接口（保留）
| 信号 | 引脚 | 说明 |
|------|------|------|
| SWDIO | PA13 | SWD数据线 |
| SWCLK | PA14 | SWD时钟线 |

## 🔧 关键代码修改

### 1. GPIO初始化中禁用JTAG
```c
// 禁用JTAG，保留SWD调试功能
AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
```

### 2. 定时器初始化前禁用JTAG
```c
void TIM_Init_All(void) {
    DisableJTAG();  // 先禁用JTAG
    // ... 然后配置定时器
}
```

### 3. I2C引脚更改
- 从PA15/PA14改为PA6/PA7
- 避开调试引脚冲突

### 4. NRF24L01引脚分离
- CE: PA3
- CSN: PA4
- 两个引脚独立控制

## ⚠️ 重要提示

1. **调试器连接**: 修正后可以正常使用ST-Link调试和烧录
2. **JTAG禁用**: 代码会自动禁用JTAG，释放PB3/PB4/PA15引脚
3. **SWD保留**: PA13(SWDIO)和PA14(SWCLK)保留用于调试
4. **引脚冲突**: 所有引脚冲突已解决

## 📝 测试建议

1. 先烧录修正后的代码
2. 确认ST-Link连接正常
3. 测试舵机1(PB3)是否有PWM输出
4. 测试SCD40的I2C通信(PA6/PA7)
5. 测试NRF24L01通信

## 🎯 修正的文件列表

- ✅ `MCU1_Sensor/Core/Inc/gpio.h` - 修正NRF引脚定义
- ✅ `MCU1_Sensor/Core/Inc/i2c.h` - 修正I2C引脚，避开调试引脚
- ✅ `MCU1_Sensor/Core/Inc/tim.h` - 添加DisableJTAG函数声明
- ✅ `MCU1_Sensor/Core/Src/gpio.c` - 添加JTAG禁用代码
- ✅ `MCU1_Sensor/Core/Src/tim.c` - 实现DisableJTAG函数
