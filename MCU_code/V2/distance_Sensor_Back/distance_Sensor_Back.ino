#include <SoftwareSerial.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define dhtPin 3
#define dhtType DHT11 
#define MPU6050_addr 0x68
#define TP 4
#define EP 5

SoftwareSerial Serial4(12,10);
DHT dht(dhtPin, dhtType);
Adafruit_MPU6050 mpu6050;
//
//int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
//int minVal=265;
//int maxVal=402;
//
//float fixax,fixdx;
//float fixay,fixdy;
//float fixaz,fixdz;
//
//double ax,dx;
//double ay,dy;
//double az,dz;
double h,t;
double distanceB;
