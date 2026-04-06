#include <Arduino_GFX_Library.h>
#include <bb_captouch.h>
#include "pins.h"
#include "gfx.h"
#include "cube.h"

void button(){
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
	button();
	CUBE();
}
