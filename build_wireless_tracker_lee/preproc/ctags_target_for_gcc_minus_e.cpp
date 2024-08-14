# 1 "/Users/living/code/github/anhuan/wireless_tracker_lee/wireless_tracker_lee.ino"
# 2 "/Users/living/code/github/anhuan/wireless_tracker_lee/wireless_tracker_lee.ino" 2


# 5 "/Users/living/code/github/anhuan/wireless_tracker_lee/wireless_tracker_lee.ino" 2
HT_st7735 st7735;





test_status_t test_status;

bool deep_sleep_flag = false;
bool interrupt_flag = false;
bool switch_test_function = false;

void interrupt_GPIO0(void)
{
 interrupt_flag = true;
 switch_test_function = true;
}

void VextON(void)
{
 pinMode(Vext, 0x03);

 digitalWrite(Vext, 0x1);



}

void VextOFF(void) // Vext default OFF
{
 pinMode(Vext, 0x03);

 digitalWrite(Vext, 0x0);



}

void enter_deepsleep(void)
{
 Radio.Sleep();
 SPI.end();
 pinMode(14, 0xC0);
 pinMode(8, 0xC0);
 pinMode(12, 0xC0);
 pinMode(13, 0xC0);
 pinMode(9, 0xC0);
 pinMode(11, 0xC0);
 pinMode(10, 0xC0);
 esp_sleep_enable_timer_wakeup(600 * 1000 * (uint64_t)1000);
 esp_deep_sleep_start();
}

void setup()
{
 HWCDCSerial.begin(115200);
 Mcu.begin(34, 0);

 st7735.st7735_init();
 st7735.st7735_fill_screen(0x0000);
 st7735.st7735_write_str(0, 0, (String) "Tracker Test Start", Font_7x10, 0xFFFF, 0x0000);
 delay(1000);
 attachInterrupt(0, interrupt_GPIO0, 0x02);
}

void loop()
{
 static uint32_t count = 10;
 static bool init = true;
 switch (count % 11)
 {
 case 0: // ble test
 {
  if (init)
  {
   init = false;
   ble_init();
  }
  if (ble_loop())
  {
   HWCDCSerial.println("end of ble loop");
   count++;
   init = true;
  }
  break;
 }
 case 1: // gps test
 {
  if (init)
  {
   init = false;
   gps_init();
  }
  if (gps_loop())
  {
   HWCDCSerial.println("end of gps loop");
   count++;
   init = true;
  }
  break;
 }
 case 2: // battery test
 {
  if (init)
  {
   init = false;
   battery_init();
  }
  if (battery_loop())
  {
   HWCDCSerial.println("end of battery loop");
   count++;
   init = true;
  }
  break;
 }
 case 3: // gsensor test
 {
  if (init)
  {
   init = false;
   gsensor_init();
  }
  if (gsensor_loop())
  {
   HWCDCSerial.println("end of gsensor loop");
   count++;
   init = true;
  }
  break;
 }
 case 4: // lora test
 {
  if (init)
  {
   init = false;
   lora_init();
  }
  if (lora_loop())
  {
   HWCDCSerial.println("end of lora loop");
   count++;
   init = true;
  }
  break;
 }
 case 5: // sd test
 {
  if (init)
  {
   init = false;
   sd_init();
  }
  if (sd_loop())
  {
   HWCDCSerial.println("end of sd loop");
   count++;
   init = true;
  }
  break;
 }
 case 6: // dsp310
 {
  if (init)
  {
   init = false;
   dsp310_init();
  }
  if (dsp310_loop())
  {
   HWCDCSerial.println("end of dsp310 loop");
   count++;
   init = true;
  }
  break;
 }
 case 7: // led
 {
  if (init)
  {
   init = false;
   led_init();
  }
  if (led_loop())
  {
   HWCDCSerial.println("end of led loop");
   count++;
   init = true;
  }
  break;
 }
 case 8: // button
 {
  if (init)
  {
   init = false;
   button_init();
  }
  if (button_loop())
  {
   HWCDCSerial.println("end of button loop");
   count++;
   init = true;
  }
  break;
 }
 case 9: // lorawan test
 {
  if (init)
  {
   init = false;
   lorawan_init();
  }
  if (lorawan_loop())
  {
   HWCDCSerial.println("end of lorawan loop");
   count++;
   init = true;
  }
  break;
 }
 case 10: // lorawan_gps test
 {
  if (init)
  {
   init = false;
   lorawan_gps_init();
  }
  if (lorawan_gps_loop())
  {
   HWCDCSerial.println("end of lorawan loop");
   count++;
   init = true;
  }
  break;
 }
 default:
 {
  count = 0;
  break;
 }
 }
}

// void tracker_v3_test_init(void)
// {
// 	st7735.st7735_fill_screen(ST7735_BLACK);
// 	pinMode(BUTTON, INPUT_PULLUP);
// 	pinMode(LED_PIN, OUTPUT);
// 	pinMode(BUZZER, OUTPUT);
// 	pinMode(ADC_Ctrl, OUTPUT);
// 	digitalWrite(ADC_Ctrl, HIGH);
// 	pinMode(pDIO1, INPUT_PULLUP);
// 	pinMode(PMC, INPUT_PULLUP);
// }

// void tracker_test_header(void)
// {
// 	st7735.st7735_write_str(0, 0, (String) "Tracker Test", Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 	adc5v_test();
// 	extern uint32_t adc5Voltage;
// 	if (adc5Voltage > 2000)
// 	{
// 		st7735.st7735_write_str(0, 12, "USB", Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 	}
// 	else
// 	{
// 		st7735.st7735_write_str(0, 12, "BATTERY", Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 	}
// 	battery_test();
// 	extern uint32_t batteryVoltage;
// 	String battery_power = "BAT: " + (String)batteryVoltage;
// 	st7735.st7735_write_str(80, 12, battery_power, Font_7x10, ST7735_WHITE, ST7735_BLACK);
// }

// bool gsensor_initialed = false;
// bool sd_initialed = false;
// bool dsp_initialed = false;
// bool lora_initialed = false;
// bool ble_initialed = false;
// bool emc_button_pressed = false;
// bool dio1_button_pressed = false;
// bool dio2_button_pressed = false;
// void reset_test_status(void)
// {
// 	gsensor_initialed = false;
// 	sd_initialed = false;
// 	dsp_initialed = false;
// 	lora_initialed = false;
// 	ble_initialed = false;
// }

// void tracker_v3_test(void)
// {
// 	static int init = 0;
// 	if (!init)
// 	{
// 		tracker_v3_test_init();
// 		init++;
// 	}
// 	emc_button_pressed = !digitalRead(BUTTON);
// 	if (emc_button_pressed)
// 	{
// 		Serial.println("Button Pressed");
// 		digitalWrite(BUZZER, HIGH);
// 	}
// 	else
// 	{
// 		Serial.println("Button Released");
// 		digitalWrite(BUZZER, LOW);
// 	}

// 	while (!digitalRead(pDIO1))
// 	{
// 		st7735.st7735_fill_screen(ST7735_BLACK);
// 		st7735.st7735_write_str(0, 20, "DIO1_PRESSED", Font_11x18, ST7735_MAGENTA, ST7735_BLACK);
// 	}
// 	while (!digitalRead(PMC))
// 	{
// 		st7735.st7735_fill_screen(ST7735_BLACK);
// 		st7735.st7735_write_str(0, 20, "PMC_PRESSED", Font_11x18, ST7735_MAGENTA, ST7735_BLACK);
// 	}

// 	static int count = 2;
// 	if (test_switch)
// 	{
// 		test_switch = false;
// 		count++;
// 	}
// 	String string_buffer1;
// 	String string_buffer2;

// 	switch (count % 7)
// 	{
// 	case 0:
// 		COLOR_LED((COLOR(count % 5)));
// 		digitalWrite(ST7735_LED_K_Pin, HIGH);
// 		if (!gsensor_initialed)
// 		{
// 			reset_test_status();
// 			gsensor_initialed = true;
// 			st7735.st7735_fill_screen(ST7735_BLACK);
// 			gsensor_init();
// 		}
// 		extern int16_t ax, ay, az;
// 		extern int16_t gx, gy, gz;
// 		gsensor_test();
// 		string_buffer1 = "ax:" + (String)ax + " ay:" + (String)ay + " az:" + (String)az;
// 		string_buffer2 = "gx:" + (String)gx + " gy:" + (String)gy + " gz:" + (String)gz;
// 		tracker_test_header();
// 		st7735.st7735_write_str(110, 0, "Gsnr", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
// 		st7735.st7735_write_str(0, 30, string_buffer1, Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 		st7735.st7735_write_str(0, 50, string_buffer2, Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 		break;
// 	case 1:
// 		COLOR_LED((COLOR(count % 5)));

// 		if (!dsp_initialed)
// 		{
// 			reset_test_status();
// 			gsensor_initialed = false;
// 			dsp_initialed = true;
// 			st7735.st7735_fill_screen(ST7735_BLACK);
// 			dsp310_init();
// 		}
// 		extern float temperature;
// 		extern float pressure;
// 		dsp310_fetch();
// 		string_buffer1 = "temperature:" + (String)temperature;
// 		string_buffer2 = "pressure:" + (String)pressure;
// 		tracker_test_header();
// 		st7735.st7735_write_str(110, 0, "DSP310", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
// 		st7735.st7735_write_str(0, 30, string_buffer1, Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 		st7735.st7735_write_str(0, 50, string_buffer2, Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 		break;
// 	case 2:
// 		COLOR_LED((COLOR(count % 5)));

// 		// if (!lora_initialed)
// 		// {
// 		// 	reset_test_status();
// 		// 	lora_initialed = true;
// 		// 	st7735.st7735_fill_screen(ST7735_BLACK);
// 		// 	lora_init();
// 		// }
// 		// tracker_test_header();
// 		// st7735.st7735_write_str(110, 0, "Lora", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
// 		// st7735.st7735_write_str(0, 24, "TX:", Font_7x10, ST7735_GREEN, ST7735_BLACK);
// 		// st7735.st7735_write_str(0, 36, txpacket, Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 		// st7735.st7735_write_str(0, 48, "RX:", Font_7x10, ST7735_GREEN, ST7735_BLACK);
// 		// st7735.st7735_write_str(0, 60, rxpacket, Font_7x10, ST7735_WHITE, ST7735_BLACK);
// 		// lora_status_handle();
// 		break;
// 	case 3:
// 		COLOR_LED((COLOR(count % 5)));

// 		st7735.st7735_fill_screen(ST7735_BLACK);
// 		tracker_test_header();
// 		gps_test();
// 		break;
// 	case 4:
// 		COLOR_LED((COLOR(count % 5)));

// 		if (!ble_initialed)
// 		{
// 			reset_test_status();
// 			ble_initialed = true;
// 			st7735.st7735_fill_screen(ST7735_BLACK);
// 			ble_init();
// 			st7735.st7735_write_str(50, 20, "BLE", Font_16x26, ST7735_MAGENTA, ST7735_BLACK);
// 			delay(1000);
// 		}
// 		ble_test();
// 		break;
// 	case 5:
// 		COLOR_LED((COLOR(count % 5)));

// 		if (!sd_initialed)
// 		{
// 			reset_test_status();
// 			sd_initialed = true;
// 			st7735.st7735_fill_screen(ST7735_BLACK);
// 			tracker_test_header();
// 			sd_init();
// 			extern bool sdInitialized;
// 			if (sdInitialized)
// 			{
// 				st7735.st7735_write_str(0, 24, "SD Init Success", Font_7x10, ST7735_GREEN, ST7735_BLACK);
// 			}
// 			else
// 			{
// 				break;
// 			}
// 		}
// 		tracker_test_header();
// 		extern bool sd_write_success;
// 		st7735.st7735_write_str(110, 0, "SD", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
// 		if (sd_write_success)
// 		{
// 			st7735.st7735_write_str(0, 36, "Hello, SD card ^_^", Font_7x10, ST7735_GREEN, ST7735_BLACK);
// 			st7735.st7735_write_str(0, 48, "Successfully wrote to file", Font_7x10, ST7735_GREEN, ST7735_BLACK);
// 		}
// 		sd_test();
// 		break;
// 	case 6:
// 		COLOR_LED((COLOR(count % 5)));

// 		st7735.st7735_fill_screen(ST7735_BLACK);
// 		tracker_test_header();
// 		digitalWrite(ST7735_LED_K_Pin, HIGH);
// 		st7735.st7735_write_str(0, 30, "Screen backlight on", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
// 		delay(500);
// 		digitalWrite(ST7735_LED_K_Pin, LOW);
// 		st7735.st7735_write_str(0, 30, "Screen backlight off - you never see me", Font_7x10, ST7735_MAGENTA, ST7735_BLACK);
// 		delay(500);
// 		break;
// 	}
// 	delay(10);
// }
