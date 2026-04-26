#ifndef __RELAY_H
#define __RELAY_H

#include "stm32f10x.h"
#include <stdbool.h>

void Relay_Init(void);
void Relay_On(void);
void Relay_Off(void);
void Buzzer_On(void);
void Buzzer_Off(void);

#endif
