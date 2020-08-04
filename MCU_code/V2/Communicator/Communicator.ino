#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <RTClib.h>

#define MP 36 //Motor permission
#define S2 22 //distance[R]
#define S3 23 //distance[L]
#define S4 26 //distance[B]
#define S5 29 //speedSensor
#define S6 42 //ESP
#define S7 35 //CTRL
#define S8 39 //Heat n Gsensor
#define S9 42 //caculation
#define S10 43 //Brake [F]
#define S11 45 //Brake [B]
#define S12 47 //Xavier
#define S13 49 //distance[F]

SoftwareSerial Serial4 (22,23);
SoftwareSerial Serial5 (24,25);
SoftwareSerial Serial9 (26,27);
SoftwareSerial Serial7 (28,29);
SoftwareSerial Serial8 (30,32);

File file;  //SD card 

RTC_DS3231 rtc;

DateTime dt;  //variable of type DateTime

bool RTCS = 0;

int BP = 0; //BattereyP
int MT = 0; //Motor Temperature
int speed = 0; //speed
int EC = 0; //Error code
int bluetoothStatus = 0;

unsigned long times = 0;

String statusForBluetooth = "";
String fileName;

void loop() {
  SerialEvent();
  if (millis()/1000>times){
    STATE();
    boardCheck();
    times++;
  }
}
