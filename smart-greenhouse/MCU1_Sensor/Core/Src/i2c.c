#include "i2c.h"
#include "main.h"

#define SDA_H()  GPIOA->BSRR = I2C_SDA_PIN
#define SDA_L()  GPIOA->BRR = I2C_SDA_PIN
#define SCL_H()  GPIOA->BSRR = I2C_SCL_PIN
#define SCL_L()  GPIOA->BRR = I2C_SCL_PIN
#define SDA_READ() (GPIOA->IDR & I2C_SDA_PIN)

static void I2C_Delay(void) {
    for(volatile int i = 0; i < 10; i++);
}

void I2C_Init_All(void) {
    // GPIO已在GPIO_Init_All中初始化
    SDA_H();
    SCL_H();
}

void I2C_Start(void) {
    SDA_H();
    SCL_H();
    I2C_Delay();
    SDA_L();
    I2C_Delay();
    SCL_L();
}

void I2C_Stop(void) {
    SDA_L();
    SCL_L();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SDA_H();
    I2C_Delay();
}

void I2C_Ack(void) {
    SDA_L();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
}

void I2C_NAck(void) {
    SDA_H();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    SCL_L();
    I2C_Delay();
}

uint8_t I2C_WaitAck(void) {
    uint8_t ack;
    SDA_H();
    I2C_Delay();
    SCL_H();
    I2C_Delay();
    ack = SDA_READ() ? 1 : 0;
    SCL_L();
    return ack;
}

void I2C_SendByte(uint8_t data) {
    for(uint8_t i = 0; i < 8; i++) {
        if(data & 0x80) SDA_H();
        else SDA_L();
        I2C_Delay();
        SCL_H();
        I2C_Delay();
        SCL_L();
        data <<= 1;
    }
}

uint8_t I2C_ReceiveByte(uint8_t ack) {
    uint8_t data = 0;
    SDA_H();
    for(uint8_t i = 0; i < 8; i++) {
        data <<= 1;
        SCL_H();
        I2C_Delay();
        if(SDA_READ()) data |= 1;
        SCL_L();
        I2C_Delay();
    }
    if(ack) I2C_Ack();
    else I2C_NAck();
    return data;
}
