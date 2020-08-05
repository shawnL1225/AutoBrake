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

SoftwareSerial Serial4 (A13,23);
SoftwareSerial Serial5 (A14,25);
SoftwareSerial Serial6 (A8,27);
SoftwareSerial Serial7 (A15,48);
SoftwareSerial Serial8 (A11,A12);
SoftwareSerial Serial9 (A9,A10);

File file;  //SD card 

RTC_DS3231 rtc;

DateTime dt;  //variable of type DateTime

bool RTCS = 0;

int BP = 0; //BattereyP
int MT = 0; //Motor Temperature
int speed = 0; //speed
int EC = 0; //Error code
int bluetoothStatus = 0;

unsigned short times = 0;

String statusForBluetooth = "";
String fileName;

void loop() {
  SerialEvent();
  if (millis()/2000>times){
    Serial1.println("AT+STATE");
//    if (Serial) boardCheck();
    times++;
  }
}
