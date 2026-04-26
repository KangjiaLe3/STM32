#ifndef __TIM_H
#define __TIM_H

#include "stm32f10x.h"

// KPZ32 PWM舵机接口使用的定时器通道
// PB3 - TIM2_CH2
// PB8 - TIM4_CH3
// PB9 - TIM4_CH4

void TIM_Init_All(void);

#endif
