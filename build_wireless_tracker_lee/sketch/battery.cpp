#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/battery.cpp"
#include "global.h"

/*!
 * ADC maximum value
 */
#define BAT_MAX_VALUE 793 // 4.2V
#define BAT_MIN_VALUE 588 // 3.3V

uint32_t batteryVoltage = 0;
uint16_t BatteryMeasureVolage(void)
{
}

void battery_init(void)
{
  switch_test_function = false;
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(50);
  st7735.st7735_write_str(0, 30, (String) "BAT INIT", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  delay(50);
  Serial.println("bat init");
  delay(1000);
  st7735.st7735_fill_screen(ST7735_BLACK);

  pinMode(ADC_Ctrl, OUTPUT);
  digitalWrite(ADC_Ctrl, HIGH);
}

float get_battery_voltage(void)
{
  float rst = 0;
  pinMode(ADC_Ctrl, OUTPUT);
  digitalWrite(ADC_Ctrl, HIGH);
  delay(10);
  uint32_t vDiv = analogReadMilliVolts(ADC_IN);

  // Divider bridge VBAT<->390k - <-- | --> - 100k <->GND => vBat = 4.9 * vDiv
  batteryVoltage = 49 * vDiv;
  batteryVoltage = batteryVoltage / 10 + 320;
  rst = batteryVoltage / 1000.0;
  digitalWrite(ADC_Ctrl, LOW);

  return rst;
}

bool battery_loop(void)
{
  uint32_t vDiv = analogReadMilliVolts(ADC_IN);

  // Divider bridge VBAT<->390k - <-- | --> - 100k <->GND => vBat = 4.9 * vDiv
  batteryVoltage = 49 * vDiv;
  batteryVoltage = batteryVoltage / 10 + 320;
  delay(2);
  Serial.println(batteryVoltage);
  delay(50);
  String batt_string = "battery Voltage: " + (String)batteryVoltage;
  st7735.st7735_write_str(110, 0, "BAT", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
  st7735.st7735_write_str(0, 30, batt_string, Font_7x10, ST7735_CYAN, ST7735_BLACK);
  if (switch_test_function)
  {
    switch_test_function = false;
    digitalWrite(ADC_Ctrl, LOW);
    st7735.st7735_fill_screen(ST7735_BLACK);
    return true;
  }
  else
  {
    return false;
  }
}