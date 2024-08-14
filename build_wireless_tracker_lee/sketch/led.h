#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/led.h"
#ifndef _LED_H
#define _LED_H
#include "global.h"

enum COLOR
{
  OFF = 0,
  RED = 2,
  GREEN = 1,
  BLUE = 3,
  WHITE = 4
};

void led_test(void);
void COLOR_LED(COLOR color);

void led_init(void);

bool led_loop(void);

#endif