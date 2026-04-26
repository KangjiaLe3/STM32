#include "main.h"
#include "../../Common/protocol.h"
#include "../Drivers/NRF24L01/nrf24l01.h"
#include "../Drivers/OLED/oled.h"
#include "../App/display.h"

volatile uint32_t system_ticks = 0;
SensorData_t sensor_data = {0};

int main(void) {
    SystemClock_Config();
    SysTick_Config(SystemCoreClock / 1000);

    GPIO_Init_All();
    I2C_Init_All();
    SPI_Init_All();

    OLED_Init();
    NRF24L01_Init();

    delay_ms(1000);

    while(1) {
        if(NRF24L01_Receive((uint8_t*)&sensor_data, DATA_PACKET_SIZE)) {
            Display_Update(&sensor_data);
        }
        delay_ms(10);
    }
}

void SystemClock_Config(void) {
    RCC->CR |= RCC_CR_HSEON;
    while(!(RCC->CR & RCC_CR_HSERDY));

    FLASH->ACR |= FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_2;

    RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9;
    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

void SysTick_Handler(void) {
    system_ticks++;
}

void delay_ms(uint32_t ms) {
    uint32_t start = system_ticks;
    while((system_ticks - start) < ms);
}

uint32_t millis(void) {
    return system_ticks;
}
