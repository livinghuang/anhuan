#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/psensor.cpp"
#include "global.h"

Dps310 Dps310PressureSensor = Dps310();

void dsp310_init()
{
  switch_test_function = false;
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(50);
  st7735.st7735_write_str(0, 30, (String) "DSP310 INIT", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  delay(50);
  Serial.println("DSP310 init");
  delay(1000);
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(10);

  pinMode(Vext, OUTPUT);
#ifdef WIFI_TRK_VER_11
  digitalWrite(Vext, HIGH);
#else
  digitalWrite(Vext, LOW);
#endif

  delay(10);

  Wire.setPins(PSENSOR_I2C_SDA, PSENSOR_I2C_SCL);
  // Call begin to initialize Dps310PressureSensor
  // The parameter 0x76 is the bus address. The default address is 0x77 and does not need to be given.
  // Dps310PressureSensor.begin(Wire, 0x76);
  // Use the commented line below instead of the one above to use the default I2C address.
  // if you are using the Pressure 3 click Board, you need 0x76
  Dps310PressureSensor.begin(Wire, 0x77);
  Serial.println("Init complete!");
}

float temperature;
float pressure;
bool dsp310_loop(void)
{

  uint8_t oversampling = 7;
  int16_t ret;
  Serial.println();

  // lets the Dps310 perform a Single temperature measurement with the last (or standard) configuration
  // The result will be written to the paramerter temperature
  // ret = Dps310PressureSensor.measureTempOnce(temperature);
  // the commented line below does exactly the same as the one above, but you can also config the precision
  // oversampling can be a value from 0 to 7
  // the Dps 310 will perform 2^oversampling internal temperature measurements and combine them to one result with higher precision
  // measurements with higher precision take more time, consult datasheet for more information
  ret = Dps310PressureSensor.measureTempOnce(temperature, oversampling);

  if (ret != 0)
  {
    // Something went wrong.
    // Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" degrees of Celsius");
  }

  // Pressure measurement behaves like temperature measurement
  // ret = Dps310PressureSensor.measurePressureOnce(pressure);
  ret = Dps310PressureSensor.measurePressureOnce(pressure, oversampling);
  if (ret != 0)
  {
    // Something went wrong.
    // Look at the library code for more information about return codes
    Serial.print("FAIL! ret = ");
    Serial.println(ret);
  }
  else
  {
    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.println(" Pascal");
  }

  String string_buffer1 = "Temperature:" + (String)temperature + " degC";
  String string_buffer2 = "Pressure:" + (String)pressure + " Pascal";
  st7735.st7735_write_str(110, 0, "Psnr", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
  st7735.st7735_write_str(0, 30, string_buffer1, Font_7x10, ST7735_WHITE, ST7735_BLACK);
  st7735.st7735_write_str(0, 50, string_buffer2, Font_7x10, ST7735_WHITE, ST7735_BLACK);

  // Wait some time
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
