#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <RTClib.h>

#define SERIAL_BUFFER_SIZE 1024
#define MP 66 //Motor permission
#define MPU6050_addr 0x68

SoftwareSerial Serial4 (67,23);
SoftwareSerial Serial5 (68,25);
//SoftwareSerial Serial6 (62,27);
SoftwareSerial Serial7 (69,48);
SoftwareSerial Serial8 (65,66);
//SoftwareSerial Serial9 (63,64);  {S2}

File file;  //SD card 

RTC_DS3231 rtc;

DateTime dt;  //variable of type DateTime

bool RTCS = 1;

int MT = 0; //Motor Temperature
int bluetoothStatus = 7;
int batteryP = 0; //BattereyP
int Btimes = 0;
//int16_t AcX,AcY,AcZ,GyX,GyY,GyZ;
//int minVal=265;
//int maxVal=402;
//
//float fixdx;
//float fixdy;
//float fixdz;
float nowSpeed = 0; //speed
//
//double dx;
//double dy;
//double dz;

unsigned short times = 0;
unsigned long S1T = 0 ;

char statusForBluetooth= '=';

String errC = "";
String fileName = "";

void loop() {
  SerialEvent(); 
  if (millis()/2000>times){
//    Serial1.println("AT+STATE");
    times++;
    delay(150);
    Serial1.print('B');
    Serial1.print(random(90,92));
    Serial1.print('|');
  }
  if (millis()/60000>Btimes){
    Btimes++;
    batteryP=batteryP- 1;
    Serial1.print('B');
    Serial1.print(batteryP);
    Serial1.print('|');
  }
//  gyro();
}
