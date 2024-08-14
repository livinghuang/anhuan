#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/lorawan.h"
#ifndef lorawan_h
#define lorawan_h
#include "global.h"

void lorawan_init();
bool lorawan_loop();
void lorawan_gps_init();
bool lorawan_gps_loop();
#endif