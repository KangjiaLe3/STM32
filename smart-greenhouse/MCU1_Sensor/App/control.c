#include "control.h"
#include "../Drivers/Servo/servo.h"
#include "../Drivers/Relay/relay.h"
#include "../Core/Inc/gpio.h"
#include "../../Common/config.h"

static bool key1_pressed = false;
static bool key2_pressed = false;
static uint8_t control_mode = MODE_AUTO;  // 默认自动模式

void Control_Init(void) {
    control_mode = MODE_AUTO;
}

void Control_SetMode(uint8_t mode) {
    control_mode = mode;
}

uint8_t Control_GetMode(void) {
    return control_mode;
}

void Control_AutoMode(SensorData_t *data) {
    // 只有在自动模式下才执行自动控制
    if(control_mode != MODE_AUTO) {
        return;
    }

    // 温度过高，开启舵机（通风窗）
    if(data->temperature > TEMP_HIGH_THRESHOLD) {
        Servo_AllOpen();
        data->servo_state = 1;
    } else {
        Servo_AllClose();
        data->servo_state = 0;
    }

    // 湿度过低或土壤湿度低，开启水泵和蜂鸣器
    if(data->humidity < HUMIDITY_LOW_THRESHOLD ||
       data->soil_moisture < SOIL_MOISTURE_LOW) {
        Relay_On();
        Buzzer_On();
        data->relay_state = 1;
        data->buzzer_state = 1;
    } else {
        Relay_Off();
        Buzzer_Off();
        data->relay_state = 0;
        data->buzzer_state = 0;
    }

    data->control_mode = MODE_AUTO;
}

void Control_ManualMode(SensorData_t *data) {
    // 修正：读取GPIOA而不是GPIOB
    // 按键1控制舵机并切换到手动模式
    if(!(GPIOA->IDR & KEY1_PIN)) {
        if(!key1_pressed) {
            key1_pressed = true;
            control_mode = MODE_MANUAL;  // 切换到手动模式
            if(data->servo_state) {
                Servo_AllClose();
                data->servo_state = 0;
            } else {
                Servo_AllOpen();
                data->servo_state = 1;
            }
        }
    } else {
        key1_pressed = false;
    }

    // 按键2控制水泵并切换到手动模式
    if(!(GPIOA->IDR & KEY2_PIN)) {
        if(!key2_pressed) {
            key2_pressed = true;
            control_mode = MODE_MANUAL;  // 切换到手动模式
            if(data->relay_state) {
                Relay_Off();
                Buzzer_Off();
                data->relay_state = 0;
                data->buzzer_state = 0;
            } else {
                Relay_On();
                data->relay_state = 1;
            }
        }
    } else {
        key2_pressed = false;
    }

    data->control_mode = control_mode;
}
