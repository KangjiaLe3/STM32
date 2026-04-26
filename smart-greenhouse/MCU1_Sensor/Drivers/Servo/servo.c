#include "servo.h"
#include "../../Common/config.h"

void Servo_Init(void) {
    Servo_AllClose();
}

void Servo_SetAngle(uint8_t servo_num, uint8_t angle) {
    if(angle > 180) angle = 180;
    uint16_t pulse = SERVO_MIN_PULSE + (angle * (SERVO_MAX_PULSE - SERVO_MIN_PULSE) / 180);

    switch(servo_num) {
        case 1: TIM2->CCR2 = pulse; break;  // PB3
        case 2: TIM4->CCR3 = pulse; break;  // PB8
        case 3: TIM4->CCR4 = pulse; break;  // PB9
    }
}

void Servo_AllOpen(void) {
    Servo_SetAngle(1, 90);
    Servo_SetAngle(2, 90);
    Servo_SetAngle(3, 90);
}

void Servo_AllClose(void) {
    Servo_SetAngle(1, 0);
    Servo_SetAngle(2, 0);
    Servo_SetAngle(3, 0);
}
