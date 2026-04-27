#include <Arduino_GFX_Library.h>
#include <Meshtastic.h>
#include "pins.h"
#include "gfx.h"


HardwareSerial MeshSerial(1); //construct serial port with uart peripheral 1

void MCLIENT(){
	pinMode(43, INPUT);
	pinMode(44, INPUT); 
	gfx->fillScreen(BLACK);
	gfx->setTextSize(3);
  gfx->setCursor(10,10);
  gfx->setTextColor(SYS);
	MeshSerial.begin(115200, SERIAL_8N1, 43, 44);
	Serial.print("is this thing on");
	while(!MeshSerial){delay(10);}
	Serial.print("djashdkj");
  gfx->print("serial radio started");
	MeshSerial.print("loopback test");


	while (true){
  	if (MeshSerial.available()) {
				Serial.print("message availible:");
    	  uint8_t messagebyte = MeshSerial.read();
				   Serial.printf("%02X \r\n", messagebyte);
		} else {
			delay(10);
		}
	}
}
