#ifndef PINS_H
#define PINS_H

///////////////
/*TOUCHSCREEN*/
///////////////

#define TOUCH_SDA 16
#define TOUCH_SCL 15
#define TOUCH_INT 17
#define TOUCH_RST 18

///////
/*TFT*/
///////

#define TFT_COM 46
#define TFT_CS 10
#define TFT_SCK 12
#define TFT_MOSI 11
#define TFT_MISO 13
#define TFT_BL 45

//////////
/*RGBLED*/
//////////

#define NEOPIXEL 42

///////////
/*SD CARD*/
///////////

#define SD_CLK 38
#define SD_CMD 40
#define SD_D0 39
#define SD_D1 41
#define SD_D2 48
#define SD_D3 47

///////
/*AMP*/
///////

#define AMP_EN 1
#define AMP_MCL 4
#define AMP_BCL 5
#define AMP_OUT 6
#define AMP_CS 7
#define AMP_IN 8

///////////
/*BUTTONS*/
///////////

#define BOOT 0
#define RESET EN

////////
/*UART*/
////////

#define RX 43
#define TX 44

///////////
/*BATTERY*/
///////////

#define BAT 9

////////
/*GPIO*/
////////

//its literwally just da gpio :p

///////
/*I2C*/
///////

#define I2C_SDA 16
#define I2C_SCL 15

//////////
/*COLORS*/
//////////

//im defining these here too because its conveinent

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#endif
