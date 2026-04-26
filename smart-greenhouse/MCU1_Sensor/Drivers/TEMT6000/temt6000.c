#include "temt6000.h"
#include "../../Core/Inc/adc.h"

void TEMT6000_Init(void) {
}

uint16_t TEMT6000_Read(void) {
    return ADC_Read(TEMT6000_ADC_CHANNEL);
}
