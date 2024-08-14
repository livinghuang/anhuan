#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/sdd.cpp"
#include "global.h"

bool sdInitialized = false;
bool sdd_setting();
bool sd_write_success = false;
void sd_init(void)
{
  switch_test_function = false;
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(50);
  st7735.st7735_write_str(0, 30, (String) "SD INIT", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  delay(50);
  Serial.println("sd init");
  delay(1000);
  st7735.st7735_fill_screen(ST7735_BLACK);

  extern RadioEvents_t RadioEvents;
  Radio.Init(&RadioEvents);
  Radio.Sleep();
  SPI.end();

  pinMode(Vext, OUTPUT);
#ifdef WIFI_TRK_VER_11
  digitalWrite(Vext, HIGH);
#else
  digitalWrite(Vext, LOW);
#endif

  pinMode(RADIO_DIO_1, ANALOG);
  pinMode(RADIO_NSS, ANALOG);
  pinMode(RADIO_RESET, ANALOG);
  pinMode(RADIO_BUSY, ANALOG);
  pinMode(LORA_CLK, ANALOG);
  pinMode(LORA_MISO, ANALOG);
  pinMode(LORA_MOSI, ANALOG);

  pinMode(LORA_RST_PIN, OUTPUT);
  digitalWrite(LORA_RST_PIN, LOW);

  delay(10);
  sdInitialized = sdd_setting();

  if (sdInitialized)
  {
    Serial.println("SD卡初始化成功");
  }
  else
  {
    Serial.println("SD卡初始化失敗");
  }
}

void sd_test()
{
}

bool sdd_setting()
{
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);

  if (!SD.begin(CS_PIN, SPI, 1000000))
  {
    return false;
  }

  return true;
}
bool sd_loop(void)
{
  st7735.st7735_write_str(110, 0, "SD", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

  // 主要迴圈程式碼放在這裡
  File file = SD.open("/test.txt");
  if (file)
  {
    Serial.println("Successfully opened file:");
    while (file.available())
    {
      Serial.write(file.read());
    }
    file.close();
  }
  else
  {
    Serial.println("Failed to open file");
    st7735.st7735_write_str(0, 30, "Failed to open file", Font_7x10, ST7735_CYAN, ST7735_BLACK);
  }

  File writeFile = SD.open("/test.txt", FILE_WRITE);
  if (writeFile)
  {
    sd_write_success = true;
    String data = "Hello, SD card ^_^";
    writeFile.println(data);
    writeFile.close();
    Serial.println("Successfully wrote to file");
    st7735.st7735_write_str(0, 30, "Successfully wrote to file", Font_7x10, ST7735_CYAN, ST7735_BLACK);
  }
  else
  {
    Serial.println("Failed to write to file");
    st7735.st7735_write_str(0, 30, "Failed to write to file", Font_7x10, ST7735_CYAN, ST7735_BLACK);
  }

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