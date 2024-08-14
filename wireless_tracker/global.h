#ifndef GLOBAL_H
#define GLOBAL_H

#include "Arduino.h"
#include "WiFi.h"
#include "LoRaWan_APP.h"
#include <Wire.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include "FS.h"
#include "SD.h"
#include "SPI.h"

#include "HT_st7735.h"
#include "HT_TinyGPS++.h"

#include "MPU6050.h"

#include "bsp.h"
#include "ble.h"
#include "gps.h"
#include "battery.h"
#include "gsensor.h"
#include "lora.h"
#include "sdd.h"
#include "esp32-hal-rgb-led.h"
#include "led.h"
#include "esp32-hal.h"
#include "button.h"
#include "lorawan.h"

#ifdef WIFI_TRK_VER_11
#include "HT_st7735.h"
extern HT_st7735 st7735;
#else
#include "HT_st7736.h"
extern HT_st7736 st7735;
#endif

#include "HT_TinyGPS++.h"
#include "sdd.h"
#include "led.h"
#include "button.h"
#include "buzzer.h"
#include "gsensor.h"
#include "psensor.h"
#include "battery.h"
#include "adc5v.h"
#include "ble.h"
#include "lorawan.h"
#include "psensor.h"
#include "Dps310.h"
#include "DpsClass.h"

typedef enum
{
  WIFI_CONNECT_TEST_INIT,
  WIFI_CONNECT_TEST,
  WIFI_SCAN_TEST,
  LORA_TEST_INIT,
  LORA_COMMUNICATION_TEST,
  DEEPSLEEP_TEST,
  GPS_TEST,
  LED_TEST,
  BUZZER_TEST,
  SD_INIT,
  SD_TEST,
  LORAWAN_INIT,
  LORAWAN_TEST,
  MPU_TEST_INIT,
  MPU_TEST,
  DPS_TEST_INIT,
  DPS_TEST,
  BAT_INIT,
  BAT_TEST,
  BUTTON_TEST,
  BLE_TEST_INIT,
  BLE_TEST,
  DI_TEST,
  ADC_5V_TEST,
  TRACKER_V3_TEST
} test_status_t;

struct gps_time_t
{
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t centisecond;
};

struct global_data_t
{
  float battery_voltage;
  struct gps_time_t time;
  double latitude;
  double longitude;
};
extern struct global_data_t global_data;

extern Dps310 Dps310PressureSensor;
extern test_status_t test_status;
extern bool switch_test_function;
// extern bool deepsleepflag;
extern bool interrupt_flag;
void printHex(byte *data, int length);
#endif