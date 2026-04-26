#include "scd40.h"
#include "../../Core/Inc/i2c.h"
#include "../../Core/Inc/main.h"

void SCD40_Init(void) {
    delay_ms(1000);
    I2C_Start();
    I2C_SendByte(SCD40_ADDR << 1);
    I2C_SendByte(0x21);
    I2C_SendByte(0xB1);
    I2C_Stop();
}

uint16_t SCD40_Read(void) {
    I2C_Start();
    I2C_SendByte(SCD40_ADDR << 1);
    I2C_SendByte(0xEC);
    I2C_SendByte(0x05);
    I2C_Stop();

    delay_ms(1);

    I2C_Start();
    I2C_SendByte((SCD40_ADDR << 1) | 1);
    uint8_t msb = I2C_ReceiveByte(1);
    uint8_t lsb = I2C_ReceiveByte(1);
    I2C_ReceiveByte(0);
    I2C_Stop();

    return (msb << 8) | lsb;
}
