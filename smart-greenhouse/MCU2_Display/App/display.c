#include "display.h"
#include "../Drivers/OLED/oled.h"
#include <stdio.h>

void Display_Update(SensorData_t *data) {
    char buf[32];

    OLED_Clear();

    OLED_ShowString(0, 0, "Smart Greenhouse");

    sprintf(buf, "Temp: %.1fC", data->temperature);
    OLED_ShowString(0, 2, buf);

    sprintf(buf, "Humi: %.1f%%", data->humidity);
    OLED_ShowString(0, 3, buf);

    sprintf(buf, "Light: %d", data->light);
    OLED_ShowString(0, 4, buf);

    sprintf(buf, "CO2: %dppm", data->co2);
    OLED_ShowString(0, 5, buf);

    sprintf(buf, "Soil: %d", data->soil_moisture);
    OLED_ShowString(0, 6, buf);

    sprintf(buf, "R:%d S:%d B:%d",
            data->relay_state,
            data->servo_state,
            data->buzzer_state);
    OLED_ShowString(0, 7, buf);
}
