#include <global.h>

test_status_t test_status = LORAWAN_INIT;

void setup()
{
  test_status = LORAWAN_INIT;
}

void loop()
{
  switch (test_status)
  {
  case LORAWAN_INIT:
    lorawan_setup();
    test_status = LORAWAN_TEST;
    break;
  case LORAWAN_TEST:
    lorawan_loop();
    break;
  case LORA_TEST_INIT:
    lora_setup();
    test_status = LORA_COMMUNICATION_TEST;
    break;
  case LORA_COMMUNICATION_TEST:
    lora_loop();
    break;
  }
}