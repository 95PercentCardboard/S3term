#include <Arduino_GFX_Library.h>
#include <bb_captouch.h>
#include "pins.h"
#include "gfx.h"
#include "sdusb.h"

void Popup(){
	gfx->fillRoundRect(
		10,
		10,
		300,
		220,
		10,
		BLACK
	);
	gfx->drawRoundRect(
		10,
		10,
		300,
		220,
		10,
		GREEN
	);
}

void USB(){
	Popup();
	gfx->setCursor(0,0);
	gfx->setTextSize(1);
	gfx->print("usb starting");
	SD_USB();
}

void System(){
	gfx->setCursor(0,0);
	gfx->setTextSize(1);
	gfx->print("unassigned selection");
}


void SDCard(){
	Popup();

}

void FSMENU(){
	Serial.println("fsmenu predraw");
	    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());
    Serial.print("Free stack: ");
    Serial.println(uxTaskGetStackHighWaterMark(NULL));
	Popup();
	Serial.println("Fsmenu started");
	gfx->setCursor(20,20); //stack overflow solved but im keeping it like this
	gfx->setTextSize(1);   
	gfx->setTextColor(WHITE);
	gfx->print("    _/_/_/_/  _/  _/                      \n");
	gfx->setCursor(20,28);
	gfx->print("   _/            _/    _/_/      _/_/_/   \n");
	gfx->setCursor(20,36);
	gfx->print("  _/_/_/    _/  _/  _/_/_/_/  _/_/        \n");
	gfx->setCursor(20,44);
	gfx->print(" _/        _/  _/  _/            _/_/     \n");
	gfx->setCursor(20,52);
	gfx->print("_/        _/  _/    _/_/_/  _/_/_/ \n");

	//draw the menu options
	gfx->setTextSize(2);
	gfx->drawLine(35, 68, 285, 68, 0x4208);
	gfx->setCursor(35, 85);
	gfx->print("SD Card");
	gfx->drawLine(35, 118, 285, 118, 0x4208);
	gfx->setCursor(35, 135);
	gfx->print("USB");
	gfx->drawLine(35, 168, 285, 168, 0x4208);
	gfx->setCursor(35, 185);
	gfx->print("System");
	gfx->drawLine(35, 218, 285, 218, 0x4208);

	//start touch polling
	TOUCHINFO ti;

	while (true) {
		if (bbct.getSamples(&ti)) {
			for (int i = 0; i<ti.count; i++){
				if ((240 - ti.x[i]) > 68 && (240 - ti.x[i]) < 118){			//touch reports upsaide down and with x/y inverted so theres some
					SDCard();																							//fucked up logic here. will make touch interperator eventually.
				} else if ((240 - ti.x[i]) > 118 && (240 - ti.x[i]) < 168){
					USB();
				} else if ((240 - ti.x[i]) > 168 && (240 - ti.x[i]) < 218){
					System();
				}
			}
		}
	}
}
