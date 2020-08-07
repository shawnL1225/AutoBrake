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
#define MPU6050_addr 0x68

SoftwareSerial Serial4 (A13,23);
SoftwareSerial Serial5 (A14,25);
SoftwareSerial Serial6 (A8,27);
SoftwareSerial Serial7 (A15,48);
SoftwareSerial Serial8 (A11,A12);
SoftwareSerial Serial9 (A9,A10);

File file;  //SD card 

RTC_DS3231 rtc;

DateTime dt;  //variable of type DateTime

bool RTCS = 1;

int BP = 0; //BattereyP
int MT = 0; //Motor Temperature
int nowSpeed = 0; //speed
int bluetoothStatus = 7;
//int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;
//int minVal=265;
//int maxVal=402;
//
//float fixdx;
//float fixdy;
//float fixdz;
//
//double dx;
//double dy;
//double dz;

unsigned short times = 0;

char statusForBluetooth= '=';

String errC = "";
String fileName = "";

void loop() {
  SerialEvent(); 
  if (millis()/2000>times){
    Serial1.println("AT+STATE");
    times++;
  }
//  gyro();
}
