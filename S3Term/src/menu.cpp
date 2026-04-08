#include <Arduino_GFX_Library.h>
#include <bb_captouch.h>
#include "pins.h"
#include "gfx.h"
#include "cube.h"

void bl(){gfx->fillScreen(BLUE);}

void br(){gfx->fillScreen(RED);}

void tr(){gfx->fillScreen(YELLOW);}

void tl(){gfx->fillScreen(WHITE);}

void buttons(){
	//gfx->drawPixel(0,0,RED);
	TOUCHINFO ti;
	while (true) {
		if (bbct.getSamples(&ti)) {
			for (int i=0; i<ti.count; i++){
      Serial.print("Touch ");Serial.print(i+1);Serial.print(": ");;
      Serial.print("  x: ");Serial.print(ti.x[i]);
      Serial.print("  y: ");Serial.print(ti.y[i]);
      Serial.print("  size: ");Serial.println(ti.area[i]);
      Serial.println(' ');

			if (ti.x[i]<51){							//this is some straight nasty code and im sorry for ever writing it
				if (ti.y[i]<95) {
					bl();
				} else if (ti.y[i]>188){
					br();
				}
			} else if (ti.x[i]>189){
				if (ti.y[i]<95) {
					tl();
				} else if (ti.y[i]>188){
					tr();
				}
			}
					
    	} // for each touch point
  	} //
	}
}

void decor(){
	gfx->drawLine(0,51, 95,51, GREEN);
	gfx->drawLine(95,51, 132,19, GREEN);
	gfx->drawLine(132,19, 188,19, GREEN);
	gfx->drawLine(188,19, 225,51, GREEN);
	gfx->drawLine(225,51, 319,51, GREEN);

  gfx->drawLine(0,189, 95,189, GREEN);
  gfx->drawLine(95,189, 132,221, GREEN);
  gfx->drawLine(132,221, 188,221, GREEN);
  gfx->drawLine(188,221, 225,189, GREEN);
  gfx->drawLine(225,189, 319,189, GREEN);
}

void MENU_INIT(){
	gfx->fillScreen(BLACK);
	decor();			//they need to draw in this exact order or very
	CUBE();				//bad things will happen and i have no idea why
	buttons();

}
