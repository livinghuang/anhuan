#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/gps.cpp"
#include "global.h"

TinyGPSPlus GPS;

bool gps_finished = false;
uint8_t gps_loop_count = 0;
void gps_init()
{
  switch_test_function = false;
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(50);
  st7735.st7735_write_str(0, 30, (String) "GPS INIT", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  delay(50);

  pinMode(VGNSS_CTRL, OUTPUT);
  digitalWrite(VGNSS_CTRL, HIGH);
  Serial1.begin(115200, SERIAL_8N1, 33, 34);
  Serial.println("gps init");
  delay(5000);
  st7735.st7735_fill_screen(ST7735_BLACK);
  gps_finished = false;
}
bool gps_loop()
{
  if (Serial1.available() > 0)
  {
    if (Serial1.peek() != '\n')
    {
      GPS.encode(Serial1.read());
    }
    else
    {
      Serial1.read();
      st7735.st7735_write_str(110, 0, "GPS", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
      if (GPS.location.isUpdated())
      {
        String time_str = "TIME:" + (String)GPS.time.hour() + ":" + (String)GPS.time.minute() + ":" + (String)GPS.time.second() + ":" + (String)GPS.time.centisecond();
        st7735.st7735_write_str(0, 30, time_str, Font_7x10, ST7735_CYAN, ST7735_BLACK);
        Serial.printf(" %02d:%02d:%02d.%02d", GPS.time.hour(), GPS.time.minute(), GPS.time.second(), GPS.time.centisecond());
        Serial.println();
        String latitude = "LAT: " + (String)GPS.location.lat();
        String longitude = "LON: " + (String)GPS.location.lng();
        st7735.st7735_write_str(0, 42, latitude, Font_7x10, ST7735_CYAN, ST7735_BLACK);
        st7735.st7735_write_str(0, 54, longitude, Font_7x10, ST7735_CYAN, ST7735_BLACK);
        Serial.print("LAT: ");
        Serial.print(GPS.location.lat(), 6);
        Serial.print(", LON: ");
        Serial.print(GPS.location.lng(), 6);
        Serial.println();
        global_data.latitude = GPS.location.lat();
        global_data.longitude = GPS.location.lng();
        global_data.time.hour = GPS.time.hour();
        global_data.time.minute = GPS.time.minute();
        global_data.time.second = GPS.time.second();
        global_data.time.centisecond = GPS.time.centisecond();
        return true;
      }
      delay(1000);
      while (Serial1.read() > 0)
        ;
    }
  }
  return false;
}

void get_gps_data(void)
{
  pinMode(VGNSS_CTRL, OUTPUT);
  digitalWrite(VGNSS_CTRL, HIGH);
  Serial1.begin(115200, SERIAL_8N1, 33, 34);
  Serial.println("gps init");
  uint32_t time = millis();
  static bool first_init = true;
  while (!gps_loop())
  {
    if ((!first_init) && (millis() - time > 5000))
    {
      break;
    }
  }
  first_init = false;
}