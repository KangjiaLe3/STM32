# 控制逻辑修正说明

## 🚨 发现的严重问题

### 1. 按键读取GPIO错误
**问题**: 
- `gpio.h`中定义按键在GPIOA (PA8, PA11)
- `control.c`中却读取GPIOB的电平

**后果**: 按键完全无效，读取的是错误的GPIO端口

**修正**: 
```c
// 错误的代码
if(!(GPIOB->IDR & KEY1_PIN))

// 正确的代码
if(!(GPIOA->IDR & KEY1_PIN))
```

### 2. 手动/自动模式冲突（最严重）
**问题**: 
用户按下按键手动控制舵机/水泵后，最多几秒钟（SAMPLE_INTERVAL），主循环会执行`Control_AutoMode()`，立即根据温湿度阈值覆盖手动设置。

**场景示例**:
1. 温度28°C（未超过30°C阈值）
2. 用户按下按键1，手动打开舵机（通风窗）
3. 2秒后，主循环执行`Control_AutoMode()`
4. 自动模式检测到温度未超标，立即关闭舵机
5. 用户的手动控制被覆盖！

**修正方案**:
引入控制模式标志位：
- `MODE_AUTO (0)`: 自动模式，根据传感器数据自动控制
- `MODE_MANUAL (1)`: 手动模式，阻止自动控制

```c
static uint8_t control_mode = MODE_AUTO;

void Control_AutoMode(SensorData_t *data) {
    // 只有在自动模式下才执行自动控制
    if(control_mode != MODE_AUTO) {
        return;
    }
    // ... 自动控制逻辑
}

void Control_ManualMode(SensorData_t *data) {
    // 按键按下时切换到手动模式
    if(!(GPIOA->IDR & KEY1_PIN)) {
        if(!key1_pressed) {
            control_mode = MODE_MANUAL;  // 切换到手动模式
            // ... 手动控制逻辑
        }
    }
}
```

### 3. 结构体对齐问题
**问题**: 
`SensorData_t`结构体在不同编译器/平台上可能有不同的内存对齐方式，导致：
- MCU1发送的数据包大小与MCU2期望的不一致
- 字段偏移量不匹配
- 数据解析错误

**示例**:
```c
// 没有pack(1)时，编译器可能插入填充字节
typedef struct {
    float temperature;      // 4字节
    float humidity;         // 4字节
    uint16_t light;         // 2字节
    // 编译器可能在这里插入2字节填充！
    uint16_t co2;           // 2字节
    // ...
} SensorData_t;
```

**修正**: 
```c
#pragma pack(1)  // 强制1字节对齐
typedef struct {
    float temperature;
    float humidity;
    uint16_t light;
    uint16_t co2;
    uint16_t soil_moisture;
    uint8_t relay_state;
    uint8_t servo_state;
    uint8_t buzzer_state;
    uint8_t control_mode;  // 新增：控制模式
} SensorData_t;
#pragma pack()  // 恢复默认对齐
```

## ✅ 修正后的功能

### 控制模式切换逻辑

1. **系统启动**: 默认自动模式
2. **按下任意按键**: 切换到手动模式
3. **手动模式下**: 自动控制被禁用，用户完全控制
4. **如何恢复自动模式**: 需要添加切换机制（见下方建议）

### 建议的模式切换方案

**方案1: 长按按键切换模式**
```c
// 长按按键1超过2秒，切换回自动模式
static uint32_t key1_press_time = 0;

if(!(GPIOA->IDR & KEY1_PIN)) {
    if(!key1_pressed) {
        key1_pressed = true;
        key1_press_time = millis();
    } else if(millis() - key1_press_time > 2000) {
        // 长按2秒，切换回自动模式
        control_mode = MODE_AUTO;
    }
} else {
    if(key1_pressed && millis() - key1_press_time < 2000) {
        // 短按，手动控制舵机
        control_mode = MODE_MANUAL;
        // 翻转舵机状态
    }
    key1_pressed = false;
}
```

**方案2: 同时按下两个按键切换模式**
```c
// 同时按下按键1和按键2，切换模式
if(!(GPIOA->IDR & KEY1_PIN) && !(GPIOA->IDR & KEY2_PIN)) {
    control_mode = (control_mode == MODE_AUTO) ? MODE_MANUAL : MODE_AUTO;
}
```

**方案3: 定时自动恢复**
```c
// 手动模式5分钟后自动恢复到自动模式
static uint32_t manual_mode_start = 0;

if(control_mode == MODE_MANUAL) {
    if(manual_mode_start == 0) {
        manual_mode_start = millis();
    } else if(millis() - manual_mode_start > 300000) {  // 5分钟
        control_mode = MODE_AUTO;
        manual_mode_start = 0;
    }
}
```

## 📋 修正的文件列表

1. ✅ `Common/protocol.h`
   - 添加`#pragma pack(1)`
   - 添加`control_mode`字段
   - 添加`MODE_AUTO`和`MODE_MANUAL`宏定义

2. ✅ `MCU1_Sensor/App/control.h`
   - 添加`Control_SetMode()`函数
   - 添加`Control_GetMode()`函数

3. ✅ `MCU1_Sensor/App/control.c`
   - 修正按键读取从GPIOB改为GPIOA
   - 添加`control_mode`静态变量
   - `Control_AutoMode()`添加模式检查
   - `Control_ManualMode()`按键按下时切换到手动模式
   - 更新`data->control_mode`字段

## 🎯 测试要点

### 1. 按键功能测试
- ✅ 按键1可以控制舵机开关
- ✅ 按键2可以控制水泵开关
- ✅ 按键响应正常，无误触发

### 2. 模式切换测试
- ✅ 系统启动时为自动模式
- ✅ 按下按键后切换到手动模式
- ✅ 手动模式下自动控制被禁用
- ✅ 手动设置不会被自动模式覆盖

### 3. 自动控制测试
- ✅ 自动模式下，温度超标时自动开启舵机
- ✅ 自动模式下，湿度过低时自动开启水泵
- ✅ 自动模式下，条件恢复时自动关闭设备

### 4. 数据通信测试
- ✅ MCU1发送的数据包大小正确
- ✅ MCU2接收的数据解析正确
- ✅ 所有字段对齐无误

## ⚠️ 重要提示

1. **模式切换**: 当前实现中，一旦切换到手动模式，无法自动恢复。建议根据实际需求选择上述方案之一。

2. **OLED显示**: 建议在MCU2的OLED上显示当前控制模式（自动/手动），让用户知道系统状态。

3. **结构体大小**: 添加`control_mode`字段后，结构体大小变为21字节（4+4+2+2+2+1+1+1+1=18字节，加上可能的对齐）。使用`#pragma pack(1)`后确保为18字节。

4. **向后兼容**: 如果MCU2的代码还没更新，需要同步更新`protocol.h`和显示逻辑。

## 📝 建议的后续改进

1. 添加模式切换指示（LED或OLED显示）
2. 实现模式自动恢复机制
3. 添加模式切换的蜂鸣器提示音
4. 记录模式切换日志（如果有存储）
