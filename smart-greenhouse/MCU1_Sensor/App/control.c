#include "control.h"
#include "../Drivers/Servo/servo.h"
#include "../Drivers/Relay/relay.h"
#include "../Core/Inc/gpio.h"
#include "../../Common/config.h"

static bool key1_pressed = false;
static bool key2_pressed = false;

void Control_Init(void) {
}

void Control_AutoMode(SensorData_t *data) {
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
}

void Control_ManualMode(SensorData_t *data) {
    // 按键1控制舵机
    if(!(GPIOB->IDR & KEY1_PIN)) {
        if(!key1_pressed) {
            key1_pressed = true;
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

    // 按键2控制水泵
    if(!(GPIOB->IDR & KEY2_PIN)) {
        if(!key2_pressed) {
            key2_pressed = true;
            if(data->relay_state) {
                Relay_Off();
                data->relay_state = 0;
            } else {
                Relay_On();
                data->relay_state = 1;
            }
        }
    } else {
        key2_pressed = false;
    }
}
