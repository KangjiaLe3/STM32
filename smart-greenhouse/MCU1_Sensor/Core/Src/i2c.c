#include "i2c.h"

void I2C_Init_All(void) {
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // PB6, PB7配置为复用开漏输出
    GPIOB->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
    GPIOB->CRL |= GPIO_CRL_CNF6 | GPIO_CRL_MODE6_1;
    GPIOB->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
    GPIOB->CRL |= GPIO_CRL_CNF7 | GPIO_CRL_MODE7_1;

    I2C1->CR2 = 36;
    I2C1->CCR = 180;
    I2C1->TRISE = 37;
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C_Start(void) {
    I2C1->CR1 |= I2C_CR1_START;
    while(!(I2C1->SR1 & I2C_SR1_SB));
}

void I2C_Stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP;
}

void I2C_SendByte(uint8_t data) {
    I2C1->DR = data;
    while(!(I2C1->SR1 & I2C_SR1_TXE));
}

uint8_t I2C_ReceiveByte(uint8_t ack) {
    if(ack) I2C1->CR1 |= I2C_CR1_ACK;
    else I2C1->CR1 &= ~I2C_CR1_ACK;
    while(!(I2C1->SR1 & I2C_SR1_RXNE));
    return I2C1->DR;
}
