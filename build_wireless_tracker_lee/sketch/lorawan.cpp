#line 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/lorawan.cpp"
/* Heltec Automation LoRaWAN communication example
 *
 * Function:
 * 1. Upload node data to the server using the standard LoRaWAN protocol.
 *
 * Description:
 * 1. Communicate using LoRaWAN protocol.
 *
 * HelTec AutoMation, Chengdu, China
 * 成都惠利特自动化科技有限公司
 * www.heltec.org
 *
 * */

#include "global.h"

/* OTAA para*/
uint8_t devEui[] = {0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x06, 0x53, 0xC8};
uint8_t appEui[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t appKey[] = {0x74, 0xD6, 0x6E, 0x63, 0x45, 0x82, 0x48, 0x27, 0xFE, 0xC5, 0xB7, 0x70, 0xBA, 0x2B, 0x50, 0x45};

/* ABP para*/
uint8_t nwkSKey[] = {0x15, 0xb1, 0xd0, 0xef, 0xa4, 0x63, 0xdf, 0xbe, 0x3d, 0x11, 0x18, 0x1e, 0x1e, 0xc7, 0xda, 0x85};
uint8_t appSKey[] = {0xd7, 0x2c, 0x78, 0x75, 0x8c, 0xdc, 0xca, 0xbf, 0x55, 0xee, 0x4a, 0x77, 0x8d, 0x16, 0xef, 0x67};
uint32_t devAddr = (uint32_t)0x007e6ae1;

/*LoraWan channelsmask, default channels 0-7*/
uint16_t userChannelsMask[6] = {0x00FF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000};

/*LoraWan region, select in arduino IDE tools*/
// LoRaMacRegion_t loraWanRegion = ACTIVE_REGION; // LORAMAC_REGION_AS923_AS2

LoRaMacRegion_t loraWanRegion = LORAMAC_REGION_AS923_AS2;

/*LoraWan Class, Class A and Class C are supported*/
DeviceClass_t loraWanClass = CLASS_A;

/*the application data transmission duty cycle.  value in [ms].*/
uint32_t appTxDutyCycle = 15000;

/*OTAA or ABP*/
bool overTheAirActivation = true;

/*ADR enable*/
bool loraWanAdr = true;

/* Indicates if the node is sending confirmed or unconfirmed messages */
bool isTxConfirmed = true;

/* Application port */
uint8_t appPort = 2;
/*!
 * Number of trials to transmit the frame, if the LoRaMAC layer did not
 * receive an acknowledgment. The MAC performs a datarate adaptation,
 * according to the LoRaWAN Specification V1.0.2, chapter 18.4, according
 * to the following table:
 *
 * Transmission nb | Data Rate
 * ----------------|-----------
 * 1 (first)       | DR
 * 2               | DR
 * 3               | max(DR-1,0)
 * 4               | max(DR-1,0)
 * 5               | max(DR-2,0)
 * 6               | max(DR-2,0)
 * 7               | max(DR-3,0)
 * 8               | max(DR-3,0)
 *
 * Note, that if NbTrials is set to 1 or 2, the MAC will not decrease
 * the datarate, in case the LoRaMAC layer did not receive an acknowledgment
 */
uint8_t confirmedNbTrials = 4;

/* Prepares the payload of the frame */
static void prepareTxFrame(uint8_t port)
{
  /*appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h".
   *appDataSize max value is LORAWAN_APP_DATA_MAX_SIZE.
   *if enabled AT, don't modify LORAWAN_APP_DATA_MAX_SIZE, it may cause system hanging or failure.
   *if disabled AT, LORAWAN_APP_DATA_MAX_SIZE can be modified, the max value is reference to lorawan region and SF.
   *for example, if use REGION_CN470,
   *the max value for different DR can be found in MaxPayloadOfDatarateCN470 refer to DataratesCN470 and BandwidthsCN470 in "RegionCN470.h".
   */
  global_data.battery_voltage = get_battery_voltage();
  get_gps_data();
  appDataSize = sizeof(global_data);
  Serial.println("appDataSize:" + appDataSize);
  Serial.flush();
  // printHex((byte *)&global_data, appDataSize);
  memcpy(&appData[0], &global_data, appDataSize);
  printHex((byte *)&appData[0], appDataSize);
  Serial.flush();
  // appData[0] = 0x00;
  // appData[1] = 0x01;
  // appData[2] = 0x02;
  // appData[3] = 0x03;
}

// if true, next uplink will add MOTE_MAC_DEVICE_TIME_REQ

void lorawan_init()
{
  switch_test_function = false;
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(50);
  st7735.st7735_write_str(0, 30, (String) "LORAWAN INIT", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  delay(50);
  Serial.println("Lorawan init");
  delay(1000);
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(10);
  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);
}

bool lorawan_loop()
{
  switch (deviceState)
  {
  case DEVICE_STATE_INIT:
  {
    st7735.st7735_write_str(110, 0, "init", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

#if (LORAWAN_DEVEUI_AUTO)
    LoRaWAN.generateDeveuiByChipID();
#endif
    LoRaWAN.init(loraWanClass, loraWanRegion);
    // both set join DR and DR when ADR off
    LoRaWAN.setDefaultDR(3);
    break;
  }
  case DEVICE_STATE_JOIN:
  {
    st7735.st7735_write_str(110, 0, "join", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

    LoRaWAN.join();
    break;
  }
  case DEVICE_STATE_SEND:
  {
    st7735.st7735_write_str(110, 0, "send", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

    prepareTxFrame(appPort);
    LoRaWAN.send();
    deviceState = DEVICE_STATE_CYCLE;
    break;
  }
  case DEVICE_STATE_CYCLE:
  {
    st7735.st7735_write_str(110, 0, "cycle", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

    // Schedule next packet transmission
    txDutyCycleTime = appTxDutyCycle + randr(-APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND);
    LoRaWAN.cycle(txDutyCycleTime);
    deviceState = DEVICE_STATE_SLEEP;
    break;
  }
  case DEVICE_STATE_SLEEP:
  {
    st7735.st7735_write_str(110, 0, "sleep", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

    LoRaWAN.sleep(loraWanClass);
    break;
  }
  default:
  {
    deviceState = DEVICE_STATE_INIT;
    break;
  }
  }
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

void lorawan_gps_init()
{
  switch_test_function = false;
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(50);
  st7735.st7735_write_str(0, 30, (String) "LORAWAN GPS INIT", Font_11x18, ST7735_WHITE, ST7735_BLACK);
  delay(50);
  Serial.println("Lorawan gps init");
  delay(1000);
  st7735.st7735_fill_screen(ST7735_BLACK);
  delay(10);
  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);
}
bool lorawan_gps_loop()
{
  static bool gps_init_flag = false;

  switch (deviceState)
  {
  case DEVICE_STATE_INIT:
  {
    st7735.st7735_write_str(110, 0, "init", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
    delay(1000);
#if (LORAWAN_DEVEUI_AUTO)
    LoRaWAN.generateDeveuiByChipID();
#endif
    LoRaWAN.init(loraWanClass, loraWanRegion);
    // both set join DR and DR when ADR off
    LoRaWAN.setDefaultDR(3);
    break;
  }
  case DEVICE_STATE_JOIN:
  {
    st7735.st7735_write_str(110, 0, "join", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
    delay(1000);
    LoRaWAN.join();
    break;
  }
  case DEVICE_STATE_SEND:
  {
    st7735.st7735_write_str(110, 0, "send", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

    // if (!gps_init_flag)
    // {
    //   st7735.st7735_write_str(110, 0, "gps init", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
    //   delay(1000);
    //   gps_init_flag = true;
    //   gps_init();
    // }
    // else
    // {
    //   if (gps_loop())
    //   {
    //     st7735.st7735_write_str(110, 0, "send", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
    //     delay(1000);
    //     Serial.println("end of gps loop");
    prepareTxFrame(appPort);
    LoRaWAN.send();
    deviceState = DEVICE_STATE_CYCLE;
    //   }
    // }
    break;
  }
  case DEVICE_STATE_CYCLE:
  {
    st7735.st7735_write_str(110, 0, "cycle", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

    // Schedule next packet transmission
    txDutyCycleTime = appTxDutyCycle + randr(-APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND);
    LoRaWAN.cycle(txDutyCycleTime);
    deviceState = DEVICE_STATE_SLEEP;
    break;
  }
  case DEVICE_STATE_SLEEP:
  {
    st7735.st7735_write_str(100, 0, "sleep", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);

    LoRaWAN.sleep(loraWanClass);
    break;
  }
  default:
  {
    deviceState = DEVICE_STATE_INIT;
    break;
  }
  }
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