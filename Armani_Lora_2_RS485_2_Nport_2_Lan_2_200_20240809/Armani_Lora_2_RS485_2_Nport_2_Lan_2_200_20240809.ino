#include "global.h"
// Dps310 Opject
bool resendflag = false;
bool deepsleepflag = false;

RTC_DATA_ATTR int bootCount = 0;
uint64_t chipid;
test_status_t test_status;

void setup()
{
  Serial.begin(115200);
  // Mcu.begin();
  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);
  print_wakeup_reason();
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  resendflag = false;
  deepsleepflag = false;

  get_chip_id();
  test_status = LORA_CONTINUOUS_RECEIVE_TEST; // RS485_INIT //LORA_CONTINUOUS_RECEIVE_TEST
}

bool lora_receive_test_init = true;
bool lora_to_lorawan_repeater_first_init = true;
void loop()
{
  switch (test_status)
  {
  case LORA_CONTINUOUS_RECEIVE_TEST:
  {
    if (lora_receive_test_init == true)
    {
      lora_init();
      lora_receive_test_init = false;
    }
    if (1) // (!recevice_done)
    {
      lora_continuous_receive();
    }
    else
    {
      test_status = RS485_INIT;
    }

    break;
  }
  case RS485_INIT:
  {
    rs485_init();
    test_status = RS485_TEST;
    break;
  }
  case RS485_TEST:
  {
    rs485_status_handle();
    delay(400);
    test_status = LORA_CONTINUOUS_RECEIVE_TEST;
    lora_receive_test_init = true;
    break;
  }
  default:
    break;
  }
}
