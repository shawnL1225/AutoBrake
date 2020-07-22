#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#define S2 34 //distance[R]
#define S3 35 //distance[L]
#define S4 36 //distance[B]
#define S5 37 //speedSensor
#define S6 38 //caculation
#define S7 39 //CTRL
#define S8 40 //Heat n Gsensor
#define S9 41 //Brake [F]
#define S10 42 //Brake [B] 
#define S11 43 //Xavier
#define S12 44 //distance[F]

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
  SerialEvent();
}
