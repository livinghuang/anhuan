# Tracker LoRaWAN Project

The Tracker LoRaWAN project is built using the Arduino framework with the Heltec Wireless Tracker. It is a modified version of the Heltec Tracker LoRaWAN example, designed primarily to transmit GNSS (Global Navigation Satellite System) information over a LoRaWAN network.

## Board Configuration

1. **License Issue:**  
   Occasionally, you may encounter a license issue due to Heltec locking the LoRa/LoRaWAN code to the chip ID. You can retrieve your license key from this [Heltec resource page](https://resource.heltec.cn/search). Once you have the key, enter it using the following command: `AT+CDKEY=6B7041AAD96C746534CB80E3FD114AC8`.

2. **LoRaWAN EUI Generation:**  
   We recommend using the auto-generate feature for the LoRaWAN EUI. After powerfffing on the board, you can retrieve this information via the UART port.

3. **Mode Configuration:**  
   You can configure the board to use either OTAA (Over-The-Air Activation) or ABP (Activation By Personalization) mode based on your project requirements.