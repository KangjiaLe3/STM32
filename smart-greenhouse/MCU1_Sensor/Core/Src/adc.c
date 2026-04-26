#include "adc.h"

void ADC_Init_All(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN;

    // PA1, PA2配置为模拟输入
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);

    // ADC配置
    RCC->CFGR &= ~RCC_CFGR_ADCPRE;
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

    ADC1->CR2 |= ADC_CR2_ADON;
    delay_ms(1);

    ADC1->CR2 |= ADC_CR2_CAL;
    while(ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC_Read(uint8_t channel) {
    ADC1->SQR3 = channel;
    ADC1->CR2 |= ADC_CR2_ADON;
    while(!(ADC1->SR & ADC_SR_EOC));
    return ADC1->DR;
}

uint16_t ADC_ReadSoilMoisture(void) {
    return ADC_Read(SOIL_ADC_CHANNEL);
}
