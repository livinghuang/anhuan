#include "global.h"
void rs485_init(void)
{
  Serial.println("RS485 Init");
  pinMode(pVext, OUTPUT);
  // pinMode(pSDN, OUTPUT);

  pinMode(RADIO_RESET, OUTPUT);
  digitalWrite(RADIO_RESET, LOW);
  // digitalWrite(pSDN, HIGH);

  pinMode(RO485_RO, INPUT);  // 将RO引脚配置为输入
  pinMode(RO485_DI, OUTPUT); // 将DI引脚配置为输出
  pinMode(RO485_DE, OUTPUT);
  digitalWrite(RO485_DE, LOW); // Disable transmission initially
  Serial1.begin(115200, SERIAL_8N1, RO485_RO, RO485_DI);
  bool extern_24v = true;
  if (extern_24v == true)
  {
    digitalWrite(pVext, HIGH);
    // digitalWrite(pSDN, HIGH);
  }
}

void rs485_status_handle(void)
{
#define device_address 0x01
  // char send_485[] = "2000-0-0_8:0:0_00:14:58_48BAE5E22748_4142B_0.00000000_0.00000000_G894_P100457.35_T37.75_GGG_0_9999_172+4+40=216<=>148-216-244-296-232-244-224-232-216-276_-88_rssi"; // Example Modbus query
  Serial.print("Sent:");
  Serial.println(send_485);
  digitalWrite(RO485_DE, HIGH); // Enable transmission
  Serial1.write(send_485, strlen(send_485));
  Serial1.flush();
  digitalWrite(RO485_DE, LOW); // Disable transmission
  // delay(1000);
}
