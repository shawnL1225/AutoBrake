#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define SERIAL_BUFFER_SIZE 1024
#define MPU6050_addr 0x68

Adafruit_MPU6050 mpu6050;
SoftwareSerial Serial10 (2,3); // Front brake
SoftwareSerial Serial11 (4,5); // Back brake
SoftwareSerial Serial12 (6,7); // Xavier 
SoftwareSerial Serial13 (8,9); // distance Front
SoftwareSerial Serial4 (10,11); //Mother board

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;

float fixdx;
float fixdy;
float fixdz;
float fixax;
float fixay;
float fixaz;

double riseAngle;
double rotateAngle;
double dz;
double ax;
double ay;

bool FDR = 0; //Front distance request by Mother board

int front_dist = 4000;
int VehicleType = 0;
float nowSpeed = 0;

void loop() {
  
  SerialEvent();
//  acc();
  gyro();
  delay(500);
}
