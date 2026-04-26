#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include <stdint.h>

// ADC通道定义 (基于KPZ32传感器接口)
#define TEMT6000_ADC_CHANNEL    ADC_Channel_0  // PA0 (传感器S1)
#define SOIL_ADC_CHANNEL        ADC_Channel_2  // PA2 (传感器S3)

void ADC_Init_All(void);
uint16_t ADC_Read(uint8_t channel);
uint16_t ADC_ReadSoilMoisture(void);

#endif
