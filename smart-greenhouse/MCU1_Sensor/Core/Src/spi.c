#include "spi.h"

void SPI_Init_All(void) {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN;

    // PA5(SCK) - 复用推挽输出
    GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
    GPIOA->CRL |= GPIO_CRL_CNF5_1 | GPIO_CRL_MODE5_1;

    // PA6(MISO) - 浮空输入
    GPIOA->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;

    // PA7(MOSI) - 复用推挽输出
    GPIOA->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
    GPIOA->CRL |= GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_1;

    // SPI1配置
    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_2 | SPI_CR1_SSM | SPI_CR1_SSI;
    SPI1->CR1 |= SPI_CR1_SPE;
}

uint8_t SPI_TransferByte(uint8_t data) {
    while(!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data;
    while(!(SPI1->SR & SPI_SR_RXNE));
    return SPI1->DR;
}
