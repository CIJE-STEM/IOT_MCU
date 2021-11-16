/*
CPP file for IoT Display

*/

#include "IoT_Display.h"

IOT_Display::IOT_Display(): _display{SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,-1} {
  Serial.println("INN IOT DISPLAY CONSTRUCTOR");
}

bool IOT_Display::init(uint8_t i2c_address)
{
  
  bool success = _display.begin(SSD1306_SWITCHCAPVCC, i2c_address);
  
  _display.cp437(true); //a bug workaround in the Adafruit GFX Library
  _display.setTextSize(1);
  _display.setTextColor(WHITE); //this is a monochrome display (not white but doesnt matter)
  _display.clearDisplay();

  return success;
}

void IOT_Display::testBitmap() {

_display.clearDisplay();

_display.drawBitmap(96,47, bitmap_wifi, WIFI_WIDTH, WIFI_HEIGHT, 1);  
_display.drawBitmap(112,47,bitmap_checkmark,CHECKMARK_WIDTH,CHECKMARK_HEIGHT,1);

_display.drawBitmap(0,32, bitmap_wifi, WIFI_WIDTH, WIFI_HEIGHT, 1); 
_display.drawBitmap(17,32,bitmap_x_square,XSQR_WIDTH,XSQR_HEIGHT,1);

_display.drawBitmap(56,0,bitmap_battery_full,BATT_WIDTH,BATT_HEIGHT,1);
_display.drawBitmap(56,17,bitmap_battery_half,BATT_WIDTH,BATT_HEIGHT,1);
_display.drawBitmap(56,33,bitmap_battery_empty,BATT_WIDTH,BATT_HEIGHT,1);
_display.drawBitmap(56,49,bitmap_battery_charging,BATT_WIDTH,BATT_HEIGHT,1);
_display.display();
  
}
