#include "nrf24l01.h"
#include "../../Core/Inc/spi.h"
#include "../../Core/Inc/gpio.h"
#include "../../Core/Inc/main.h"
#include "../../Common/config.h"

#define NRF_CSN_LOW()   GPIOA->BRR = GPIO_Pin_4
#define NRF_CSN_HIGH()  GPIOA->BSRR = GPIO_Pin_4
#define NRF_CE_LOW()    GPIOB->BRR = NRF_CE_PIN
#define NRF_CE_HIGH()   GPIOB->BSRR = NRF_CE_PIN

static uint8_t NRF_ReadReg(uint8_t reg) {
    NRF_CSN_LOW();
    SPI_TransferByte(reg);
    uint8_t value = SPI_TransferByte(0xFF);
    NRF_CSN_HIGH();
    return value;
}

static void NRF_WriteReg(uint8_t reg, uint8_t value) {
    NRF_CSN_LOW();
    SPI_TransferByte(reg | 0x20);
    SPI_TransferByte(value);
    NRF_CSN_HIGH();
}

static void NRF_WriteBuf(uint8_t reg, uint8_t *buf, uint8_t len) {
    NRF_CSN_LOW();
    SPI_TransferByte(reg | 0x20);
    for(uint8_t i = 0; i < len; i++) {
        SPI_TransferByte(buf[i]);
    }
    NRF_CSN_HIGH();
}

void NRF24L01_Init(void) {
    NRF_CE_LOW();
    delay_ms(10);

    NRF_WriteReg(NRF_CONFIG, 0x0E);
    NRF_WriteReg(NRF_EN_AA, 0x01);
    NRF_WriteReg(NRF_EN_RXADDR, 0x01);
    NRF_WriteReg(NRF_SETUP_AW, 0x03);
    NRF_WriteReg(NRF_SETUP_RETR, 0x1A);
    NRF_WriteReg(NRF_RF_CH, NRF_CHANNEL);
    NRF_WriteReg(NRF_RF_SETUP, 0x07);

    uint8_t addr[5] = NRF_ADDRESS;
    NRF_WriteBuf(NRF_TX_ADDR, addr, 5);
    NRF_WriteBuf(NRF_RX_ADDR_P0, addr, 5);
    NRF_WriteReg(NRF_RX_PW_P0, 32);

    NRF24L01_TxMode();
}

bool NRF24L01_Check(void) {
    uint8_t addr[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};
    NRF_WriteBuf(NRF_TX_ADDR, addr, 5);
    uint8_t buf[5];
    for(int i = 0; i < 5; i++) {
        buf[i] = NRF_ReadReg(NRF_TX_ADDR + i);
        if(buf[i] != 0xC2) return false;
    }
    return true;
}

void NRF24L01_TxMode(void) {
    NRF_CE_LOW();
    NRF_WriteReg(NRF_CONFIG, 0x0E);
    NRF_CE_HIGH();
}

void NRF24L01_RxMode(void) {
    NRF_CE_LOW();
    NRF_WriteReg(NRF_CONFIG, 0x0F);
    NRF_CE_HIGH();
}

bool NRF24L01_Transmit(uint8_t *data, uint8_t len) {
    NRF_CE_LOW();
    NRF_CSN_LOW();
    SPI_TransferByte(NRF_CMD_W_TX_PAYLOAD);
    for(uint8_t i = 0; i < len; i++) {
        SPI_TransferByte(data[i]);
    }
    NRF_CSN_HIGH();
    NRF_CE_HIGH();
    delay_ms(1);
    NRF_CE_LOW();
    return true;
}

bool NRF24L01_Receive(uint8_t *data, uint8_t len) {
    uint8_t status = NRF_ReadReg(NRF_STATUS);
    if(status & 0x40) {
        NRF_CSN_LOW();
        SPI_TransferByte(NRF_CMD_R_RX_PAYLOAD);
        for(uint8_t i = 0; i < len; i++) {
            data[i] = SPI_TransferByte(0xFF);
        }
        NRF_CSN_HIGH();
        NRF_WriteReg(NRF_STATUS, status);
        return true;
    }
    return false;
}
