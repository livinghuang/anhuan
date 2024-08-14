#include "global.h"

MPU6050_Base MPU;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void gsensor_init()
{
  pinMode(Vext, OUTPUT);
#ifdef WIFI_TRK_VER_11
  digitalWrite(Vext, HIGH);
#else
  digitalWrite(Vext, LOW);
#endif

  switch_test_function = false;
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(50);
  st7735.st7735_write_str(0, 30, (String) "G Sensor INIT", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  delay(50);
  Serial.println("g sensor init");
  delay(1000);
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(10);
  Wire.begin(GSENSOR_I2C_SDA, GSENSOR_I2C_SCL, 100000);
  Wire.setClock(100000);
  // start test
  // Initialize communication with the MPU6050
  // Wire.begin(); // For boards with dedicated SDA, SCL pins
  // Wire.begin(SDA_PIN, SCL_PIN); // Use this for boards without dedicated I2C pins
  // Wire.setClock(400000); // Set I2C clock speed to 400kHz
  MPU.initialize(); // Initialize the MPU6050
  if (!MPU.testConnection())
  {
    Serial.println("MPU6050 connection failed");
    delay(1000);
    // while (1)
    //   ;
  }
  Serial.println("MPU6050 connection successful");
}

bool gsensor_loop(void)
{

  MPU.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("A: ");
  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.print(az);
  Serial.print(" ");

  Serial.print("G: ");
  Serial.print(gx);
  Serial.print(" ");
  Serial.print(gy);
  Serial.print(" ");
  Serial.println(gz);

  String string_buffer1 = "ax:" + (String)ax + " ay:" + (String)ay + " az:" + (String)az;
  String string_buffer2 = "gx:" + (String)gx + " gy:" + (String)gy + " gz:" + (String)gz;
  st7735.st7735_write_str(110, 0, "Gsnr", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
  st7735.st7735_write_str(0, 30, string_buffer1, Font_7x10, ST7735_WHITE, ST7735_BLACK);
  st7735.st7735_write_str(0, 50, string_buffer2, Font_7x10, ST7735_WHITE, ST7735_BLACK);
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