#include "global.h"

struct global_data_t global_data;

void printHex(byte *data, int length)
{
  for (int i = 0; i < length; i++)
  {
    // Print each byte in hexadecimal format with leading zeros
    if (data[i] < 0x10)
    {
      Serial.print("0");
    }
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println(); // Print a newline character at the end
}