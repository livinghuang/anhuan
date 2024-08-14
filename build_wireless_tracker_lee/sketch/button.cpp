#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/button.cpp"
#include "global.h"
void button_setting(void)
{
  pinMode(BUTTON, INPUT);
}

void button_test(void)
{
  int pin = digitalRead(BUTTON);
  String button_string;
  if (pin)
  {
    button_string = "released";
  }
  else
  {
    button_string = "pressed";
  }
  Serial.println(button_string);
  st7735.st7735_fill_screen(ST7735_BLACK);
  st7735.st7735_write_str(0, 40, button_string);
  delay(1000);
}

void button_init(void)
{
  switch_test_function = false;
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(50);
  st7735.st7735_write_str(0, 30, (String) "BUTTON/BUZZER INIT", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  delay(50);
  Serial.println("Button/buzzer init");
  delay(1000);
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(10);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(pDIO1, INPUT_PULLUP);
  pinMode(pDIO2, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
}
bool button_loop(void)
{
  int pin4 = digitalRead(BUTTON);
  int pin5 = digitalRead(pDIO1);
  int pin6 = digitalRead(pDIO2);
  String button_string1;
  String button_string2;
  String button_string3;

  if (pin4)
  {
    button_string1 = "pin4 released";
  }
  else
  {
    button_string1 = "pin4 pressed";
  }

  if (pin5)
  {
    button_string2 = "pin5 released";
  }
  else
  {
    button_string2 = "pin5 pressed";
  }

  if (pin6)
  {
    button_string3 = "pin6 released";
  }
  else
  {
    button_string3 = "pin6 pressed";
  }

  Serial.println(button_string1);
  Serial.println(button_string2);
  Serial.println(button_string3);

  st7735.st7735_fill_screen(ST7735_BLACK);
  st7735.st7735_write_str(0, 30, button_string1, Font_7x10, ST7735_CYAN, ST7735_BLACK);
  st7735.st7735_write_str(0, 42, button_string2, Font_7x10, ST7735_CYAN, ST7735_BLACK);
  st7735.st7735_write_str(0, 54, button_string3, Font_7x10, ST7735_CYAN, ST7735_BLACK);

  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  delay(500);

  if (switch_test_function)
  {
    switch_test_function = false;
    return true;
  }
  else
  {
    return false;
  }
}