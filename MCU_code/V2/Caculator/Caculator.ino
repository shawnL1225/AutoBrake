//===============================================================
//#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
//#include <Wire.h>
//===============================================================
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#define SERIAL_BUFFER_SIZE 1024
#define MPU6050BackAddr 0x68
#define MPU6050FrontAddr 0x69

//===============================================================
//Adafruit_MPU6050 mpu6050;
//===============================================================
SoftwareSerial Serial10 (2,3); // Front brake
SoftwareSerial Serial13 (4,5); // distance Front
//SoftwareSerial Serial12 (6,7); // Xavier 
SoftwareSerial Serial11 (6,7); // Back brake
SoftwareSerial Serial4 (8,9); //Mother board
File file;

int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;
int NO = 9999;
int times=0;
int expSetSpeed = 0;
int backBrakeForce=0;
int frontBrakeForce =0;
int front_dist = 4000;
int RFF = 0;
int RBF = 0;

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
double backRotateAngle;
double frontRotateAngle = 0;
double ax = 0;
double ay = 0;


bool FDR = 0; //Front distance request by Mother board

float nowSpeed = 0;

String fileName = "";

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void loop() {
//  SerialEvent();
//  acc();
//  gyroBack();
//  SerialEvent();
//  gyroFront();
//  SerialEvent();
//  light();
  SerialEvent();
  forceCaculate();
//  delay(500);
}
