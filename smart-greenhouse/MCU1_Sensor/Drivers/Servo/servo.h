#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"
#include <stdint.h>

// KPZ32舵机接口使用TIM2和TIM4
// 舵机1: PB3 (TIM2_CH2)
// 舵机2: PB8 (TIM4_CH3)
// 舵机3: PB9 (TIM4_CH4)

void Servo_Init(void);
void Servo_SetAngle(uint8_t servo_num, uint8_t angle);
void Servo_AllOpen(void);
void Servo_AllClose(void);

#endif
