#include "gpio.h"

void GPIO_Init_All(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;

    // 禁用JTAG，保留SWD调试功能
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;

    // DHT11 (PA1) - 推挽输出（初始化为输出，读取时会切换为输入）
    GPIOA->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    GPIOA->CRL |= GPIO_CRL_MODE1_1;

    // 继电器 (PB5) - 推挽输出
    GPIOB->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
    GPIOB->CRL |= GPIO_CRL_MODE5_1;
    GPIOB->BRR = RELAY_PIN;

    // 蜂鸣器 (PB2) - 推挽输出
    GPIOB->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
    GPIOB->CRL |= GPIO_CRL_MODE2_1;
    GPIOB->BRR = BUZZER_PIN;

    // 按键1 (PA8) - 上拉输入（修正：必须配置为上拉输入）
    GPIOA->CRH &= ~(GPIO_CRH_CNF8 | GPIO_CRH_MODE8);
    GPIOA->CRH |= GPIO_CRH_CNF8_1;  // 上拉/下拉输入
    GPIOA->BSRR = KEY1_PIN;          // 使能上拉

    // 按键2 (PA11) - 上拉输入（修正：必须配置为上拉输入）
    GPIOA->CRH &= ~(GPIO_CRH_CNF11 | GPIO_CRH_MODE11);
    GPIOA->CRH |= GPIO_CRH_CNF11_1;  // 上拉/下拉输入
    GPIOA->BSRR = KEY2_PIN;           // 使能上拉

    // NRF CE (PB0) - 推挽输出
    GPIOB->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    GPIOB->CRL |= GPIO_CRL_MODE0_1;

    // NRF CSN (PA4) - 推挽输出
    GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4);
    GPIOA->CRL |= GPIO_CRL_MODE4_1;
    GPIOA->BSRR = NRF_CSN_PIN;  // CSN默认高电平

    // NRF IRQ (PB1) - 上拉输入
    GPIOB->CRL &= ~(GPIO_CRL_CNF1 | GPIO_CRL_MODE1);
    GPIOB->CRL |= GPIO_CRL_CNF1_1;
    GPIOB->BSRR = NRF_IRQ_PIN;

    // I2C引脚 (PB6-SDA, PB7-SCL) - 开漏输出
    GPIOB->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_MODE6);
    GPIOB->CRL |= GPIO_CRL_CNF6_0 | GPIO_CRL_MODE6_1;
    GPIOB->CRL &= ~(GPIO_CRL_CNF7 | GPIO_CRL_MODE7);
    GPIOB->CRL |= GPIO_CRL_CNF7_0 | GPIO_CRL_MODE7_1;
    GPIOB->BSRR = I2C_SDA_PIN | I2C_SCL_PIN;
}
