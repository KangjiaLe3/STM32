#include "main.h"
#include "../../Common/protocol.h"
#include "../../Common/config.h"
#include "../Drivers/DHT11/dht11.h"
#include "../Drivers/SCD40/scd40.h"
#include "../Drivers/TEMT6000/temt6000.h"
#include "../Drivers/NRF24L01/nrf24l01.h"
#include "../Drivers/Servo/servo.h"
#include "../Drivers/Relay/relay.h"
#include "../App/control.h"

volatile uint32_t system_ticks = 0;
SensorData_t sensor_data = {0};

int main(void) {
    SystemClock_Config();
    SysTick_Config(SystemCoreClock / 1000);

    GPIO_Init_All();
    ADC_Init_All();
    TIM_Init_All();
    I2C_Init_All();
    SPI_Init_All();

    DHT11_Init();
    SCD40_Init();
    TEMT6000_Init();
    NRF24L01_Init();
    Servo_Init();
    Relay_Init();
    Control_Init();

    delay_ms(1000);

    uint32_t last_sample = 0;

    while(1) {
        uint32_t now = millis();

        if(now - last_sample >= SAMPLE_INTERVAL) {
            DHT11_Read(&sensor_data.temperature, &sensor_data.humidity);
            sensor_data.light = TEMT6000_Read();
            sensor_data.co2 = SCD40_Read();
            sensor_data.soil_moisture = ADC_ReadSoilMoisture();

            Control_AutoMode(&sensor_data);
            NRF24L01_Transmit((uint8_t*)&sensor_data, DATA_PACKET_SIZE);

            last_sample = now;
        }

        Control_ManualMode(&sensor_data);
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
