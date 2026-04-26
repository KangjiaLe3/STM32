#ifndef __TIM_H
#define __TIM_H

#include "stm32f10x.h"

// KPZ32 PWM舵机接口使用的定时器通道
// 修正：PB3需要禁用JTAG才能使用
// PB3 - TIM2_CH2 (需要重映射JTAG)
// PB8 - TIM4_CH3
// PB9 - TIM4_CH4

void TIM_Init_All(void);
void DisableJTAG(void);  // 禁用JTAG，释放PB3引脚

#endif
