#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "countsensor.h"
#include "encounter.h"

int16_t num=0;

int main(void)
{
	OLED_Init();
	countsensor_Init();
	encounter_Init();
	
	OLED_ShowString(1, 1, "Count:");
	
	while (1)
	{
		num += encounter_get();
		OLED_ShowSignedNum(1, 7,num, 5);
	}
}
