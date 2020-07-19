#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#define S1 33
#define S2 34
#define S3 35
#define S4 36
#define S5 37
#define S6 38
#define S7 39
#define S8 40


SoftwareSerial Serial4 (22,23);
SoftwareSerial Serial5 (24,25);
SoftwareSerial Serial6 (26,27);
SoftwareSerial Serial7 (28,29);
SoftwareSerial Serial8 (30,32);

File file;  //SD card 

int frontBrakeForce = 0;
int backBrakeForce = 0;

String statusForBluetooth = "";
String fileName;

void loop() {
  
}
