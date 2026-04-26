#include "relay.h"
#include "../../Core/Inc/gpio.h"

void Relay_Init(void) {
    Relay_Off();
    Buzzer_Off();
}

void Relay_On(void) {
    GPIOB->BSRR = RELAY_PIN;
}

void Relay_Off(void) {
    GPIOB->BRR = RELAY_PIN;
}

void Buzzer_On(void) {
    GPIOB->BSRR = BUZZER_PIN;
}

void Buzzer_Off(void) {
    GPIOB->BRR = BUZZER_PIN;
}
