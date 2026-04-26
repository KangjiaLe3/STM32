#ifndef __CONTROL_H
#define __CONTROL_H

#include "../../Common/protocol.h"
#include <stdbool.h>

void Control_Init(void);
void Control_AutoMode(SensorData_t *data);
void Control_ManualMode(SensorData_t *data);
void Control_SetMode(uint8_t mode);
uint8_t Control_GetMode(void);

#endif
