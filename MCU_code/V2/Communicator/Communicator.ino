#include <Wire.h>  
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // set lcd I2C address
File  file;           //SD card 

int fixhr=0,fixmi=0,fixsec=0,fixmsec=0;  //Add time to arduino millisecond
int Speed;
int BV;
int Temp;

double hv=0;

bool appStart=0;
bool brake=0;

String fileName, lBV/*last battery voltage*/, lsS;/*last speed String*/


void loop() {
  serialEvent();
}
