#include "dht11.h"
#include "../../Core/Inc/main.h"
#include "../../Core/Inc/gpio.h"

static void DHT11_SetOutput(void) {
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    GPIOA->CRL |= GPIO_CRL_MODE0_1;
}

static void DHT11_SetInput(void) {
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0);
    GPIOA->CRL |= GPIO_CRL_CNF0_0;
}

void DHT11_Init(void) {
    DHT11_SetOutput();
    GPIOA->BSRR = DHT11_PIN;
}

bool DHT11_Read(float *temperature, float *humidity) {
    uint8_t data[5] = {0};

    DHT11_SetOutput();
    GPIOA->BRR = DHT11_PIN;
    delay_ms(18);
    GPIOA->BSRR = DHT11_PIN;
    DHT11_SetInput();

    for(int i = 0; i < 40; i++) {
        while(!(GPIOA->IDR & DHT11_PIN));
        uint32_t count = 0;
        while(GPIOA->IDR & DHT11_PIN) {
            count++;
            if(count > 100) return false;
        }
        if(count > 30) data[i/8] |= (1 << (7 - i%8));
    }

    if(data[4] != (data[0] + data[1] + data[2] + data[3])) return false;

    *humidity = data[0] + data[1] * 0.1f;
    *temperature = data[2] + data[3] * 0.1f;
    return true;
}
