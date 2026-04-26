#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

#define NRF_CE_PORT     GPIOB
#define NRF_CE_PIN      GPIO_Pin_0
#define NRF_IRQ_PORT    GPIOB
#define NRF_IRQ_PIN     GPIO_Pin_1

void GPIO_Init_All(void);

#endif
