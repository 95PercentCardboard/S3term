#include <Arduino.h>
#include <Wire.h>
#include <SD_MMC.h>
#include <SPI.h>
#include "pins.h"

bool I2C_TEST(){
	byte error, address;
  int nDevices;

  Serial.println("Starting I2C...");

  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }
  }
  if (nDevices == 0){
    Serial.println("[  FAILED  ] No I2C devices found");
		return 0;
  } else {
		Serial.println("[  OK  ] I2C initialized");
		return 1;
	}
}


bool SD_TEST(){
	Serial.println("Starting SD scan...");
	if (!SD_MMC.begin()) {
		Serial.println("[  FAILED  ] Storage mount failed");
	}

	uint8_t cardType = SD_MMC.cardType();

	if (cardType == CARD_NONE) {
		Serial.println("[  WARNING!  ] No external storage");
		return 1;
	}

	Serial.println("[  OK  ] Storage found!");
	
	if (cardType == CARD_MMC){
		Serial.println("Type: MMC");
	} else if (cardType == CARD_SD) {
		Serial.println("Type: SDSC");
	} else if (cardType == CARD_SDHC) {
		Serial.println("Type: SDHC");
	} else {
		Serial.println("Type: UNKOWN");
	}

	uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);

	Serial.print("External storage size: ");
  Serial.print(cardSize);
  Serial.println("MB");

	return 1;
}
