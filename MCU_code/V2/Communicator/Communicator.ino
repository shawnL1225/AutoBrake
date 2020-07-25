#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

SoftwareSerial Serial4 (22,23);
SoftwareSerial Serial5 (24,25);
SoftwareSerial Serial9 (26,27);
SoftwareSerial Serial7 (28,29);
SoftwareSerial Serial8 (30,32);

File file;  //SD card 

int BP = 0; //BattereyP
int MT = 0; //Motor Temperature
int speed = 0; //speed
int EC = 0; //Error code

String statusForBluetooth = "";
String fileName;

void loop() {
  SerialEvent();
}
