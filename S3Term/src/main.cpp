#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <SD_MMC.h>
#include <bb_captouch.h>
#include "diagnostics.h"
#include "pins.h"
#include "menu.h"
#include "gfx.h"

//this has to be here for graphics to be global. i might find a better place for it later
Arduino_GFX* gfx = nullptr;

//putting another here bc i cant be bothered. i'll change if we have more globals
BBCapTouch bbct;

void setup(){
  Serial.begin(115200);
	//while(!Serial) delay(10);
	//setup screen data pins
	Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_COM, TFT_CS, TFT_SCK, TFT_MOSI , TFT_MISO);
	
	//set rotation and screen type
	gfx = new Arduino_ILI9341(bus, GFX_NOT_DEFINED, 1, true);

	//initialize touchscreen
	bbct.init(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_INT);

	//set touchscreen to be aligned with screen
	bbct.setOrientation(1, 320, 240);

	//start graphics driver and turn on screen backlight
	gfx->begin();
	pinMode(TFT_BL, OUTPUT);
	digitalWrite(TFT_BL, HIGH);

	//some hardware tests because i wanted the boot sequence to look cool
  Wire.begin(I2C_SDA, I2C_SCL);
  I2C_TEST();
	SD_MMC.setPins(SD_CLK, SD_CMD, SD_D0, SD_D1, SD_D2, SD_D3);
	SD_TEST();
	SPI.begin(TFT_SCK, TFT_MISO, TFT_MOSI);

	//pass the display object so the menu knows where to display
	MENU_INIT();
}

void loop(){}
