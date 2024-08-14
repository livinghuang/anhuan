#ifndef GLOBAL_H
#define GLOBAL_H

#include "Arduino.h"
#include "esp_system.h"
#include "LoRaWan_APP.h"
#include "bsp.h"
#include "esp_sleep.h"
#include <esp_timer.h>
#include "lora.h"
#include "rs485.h"

typedef enum
{
  LORA_CONTINUOUS_RECEIVE_TEST,
  RS485_INIT,
  RS485_TEST,
} test_status_t;

struct sensor_data
{
  float temperature;
  float humidity;
  float pressure;
  float PT100;
};

extern char send_485[];

typedef struct sensor_data sensor_data_t;
extern sensor_data_t global_sensor_result;

extern bool resendflag;
extern bool deepsleepflag;
extern bool interrupt_flag;
extern bool reset_run_with_time_escape;
extern bool recevice_done;
extern RTC_DATA_ATTR int bootCount; // 增加发送的数据包编号

void printHex(byte *data, int length);
void run_with_time_escape(uint64_t escape_period_ms, void (*callback)(), void (*stop_callback)());
esp_sleep_wakeup_cause_t print_wakeup_reason();
uint64_t get_chip_id();
#endif
