#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/battery.h"
#ifndef _BATTERY_H
#define _BATTERY_H
#include "global.h"
void battery_init(void);
bool battery_loop(void);
float get_battery_voltage(void);
#endif