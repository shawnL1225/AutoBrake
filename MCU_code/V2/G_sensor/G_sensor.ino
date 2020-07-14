#include <DHT.h>
#include<Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define dhtPin 8
#define MPU6050_addr 0x68
#define dhtType DHT11 

DHT dht(dhtPin, dhtType);
Adafruit_MPU6050 mpu6050;

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;

float fixax,fixdx;
float fixay,fixdy;
float fixaz,fixdz;

double ax,dx;
double ay,dy;
double az,dz;
double h,t;

void setup() {
  //setup
  Serial.begin(9600);
  dht.begin();
  mpu6050.begin();
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  //Error dectect
  temp();
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT Sensor Error");
  }
  Serial.println("OK");
  acc();
  gyro();
  fixax=-ax;
  fixay=-ay;
  fixaz=-az;
  fixdx=-dx;
  fixdy=-dy;
  fixdz=-dz;
}

void loop() {
  acc();
  gyro();
  temp();
  send();
}

void serialEvent(){
  if (Serial.available()>0){
    char in = Serial.read();
    if (in=='R'){
      fixax=-ax;
      fixay=-ay;
      fixaz=-az;
      fixdx=-dx;
      fixdy=-dy;
      fixdz=-dz;
    }
  }
}
