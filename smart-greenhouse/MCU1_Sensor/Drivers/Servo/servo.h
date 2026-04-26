#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"
#include <stdint.h>

void Servo_Init(void);
void Servo_SetAngle(uint8_t servo_num, uint8_t angle);
void Servo_AllOpen(void);
void Servo_AllClose(void);

#endif
