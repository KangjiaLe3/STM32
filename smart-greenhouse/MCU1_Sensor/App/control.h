#ifndef __CONTROL_H
#define __CONTROL_H

#include "../../Common/protocol.h"
#include <stdbool.h>

void Control_Init(void);
void Control_AutoMode(SensorData_t *data);
void Control_ManualMode(SensorData_t *data);

#endif
