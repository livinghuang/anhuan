#include "bsp.h"
#include "g_lora.h"
#include "g_lorawan.h"

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

extern test_status_t test_status;