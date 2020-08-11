#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define SERIAL_BUFFER_SIZE 1024
#define MPU6050_addr 0x68

Adafruit_MPU6050 mpu6050;
SoftwareSerial Serial10 (2,3);
SoftwareSerial Serial11 (4,5);
SoftwareSerial Serial12 (6,7);
SoftwareSerial Serial13 (8,9);
SoftwareSerial Serial4 (10,11);

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;

float fixdx;
float fixdy;
float fixdz;
float fixax;
float fixay;
float fixaz;

double dx;
double dy;
double dz;
double ax;
double ay;
double az;

bool A_F = 0;


void loop() {
  SerialEvent();
}
