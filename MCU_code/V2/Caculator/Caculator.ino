#include <SoftwareSerial.h>
#include <Wire.h>

#define MPU6050_addr 0x68

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

double dx;
double dy;
double dz;

bool A_F = 0;


void loop() {
  
}
