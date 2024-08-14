# Setting Up a Private LoRaWAN Environment

This document outlines the steps required to set up a private LoRaWAN environment using specific hardware and software components.

## Preparation

You will need the following components:

1. **Linxdot LD1002** as the primary LoRaWAN server.  
   [Linxdot LD1002 Operations Manual](https://living-huang.gitbook.io/linxdot-ld1002-operations-manual)

2. **Heltec HT-M7603** as a secondary LoRaWAN gateway.  
   [Heltec HT-M7603 Documentation](https://docs.heltec.cn/en/gateway/ht-m7603/index.html)

3. **TP-LINK TL-MR100** for access point (AP) functionality.  
   [TP-LINK TL-MR100 Support Page](https://www.tp-link.com/tw/support/download/tl-mr100/)

4. **Heltec Wireless Tracker** as a LoRaWAN node.  
   [Heltec Wireless Tracker Documentation](https://docs.heltec.cn/en/node/esp32/wireless_tracker/index.html)

### Hardware Setup

1. **Network Connection:**  
   Connect the TL-MR100, Linxdot LD1002, and HT-M7603 using Ethernet cables.

2. **Node Preparation:**  
   Prepare the Heltec Wireless Tracker and configure it as a LoRaWAN node.

### Initial Setup

1. **TL-MR100 Configuration:**
   - Create a Wi-Fi access point (AP) with the following settings:
     - **SSID:** `lorawan_ap`
     - **Password:** `lorawan_ap`
   - Access the setup page by navigating to `192.168.1.1` in a web browser. The login password is `lorawan`.

2. **Linxdot LD1002 Configuration:**
   - Set up the ChirpStack server on the Linxdot LD1002.
   - Access the system setup page at `192.168.1.100:8080` using the following credentials:
     - **Username:** `admin`
     - **Password:** `admin`

3. **HT-M7603 Configuration:**
   - Access the LoRaWAN concentrator settings for the HT-M7603 by navigating to `192.168.1.101`.
   - The login password is `heltec.org`.


