#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define SERIAL_BUFFER_SIZE 1024
#define MPU6050BackAddr 0x68
#define MPU6050FrontAddr 0x69

Adafruit_MPU6050 mpu6050;
SoftwareSerial Serial10 (2,3); // Front brake
SoftwareSerial Serial11 (4,5); // Back brake

SoftwareSerial Serial12 (6,7); // Xavier 
SoftwareSerial Serial13 (10,11); // distance Front
SoftwareSerial Serial4 (8,9); //Mother board

int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;

float fixFdx;
float fixFdy;
float fixFdz;
float fixBdx;
float fixBdy;
float fixBdz;
float fixax;
float fixay;
float fixaz;

double riseAngle;
double flipAngle;
double BrotateAngle;
double frontRotate;
double ax = 0;
double ay = 0;

bool FDR = 0; //Front distance request by Mother board

int front_dist = 4000;
int VehicleType = 0;
float nowSpeed = 0;

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void loop() {
  
  SerialEvent();
//  acc();
  gyroBack();
  delay(500);
}
