//===============================================================
//#include <Adafruit_MPU6050.h>
//#include <Adafruit_Sensor.h>
#include <Wire.h>
//===============================================================
#include <SoftwareSerial.h>

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

int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;
int times=0;
int expSetSpeed = 0;
int backBrakeForce=9999;
int frontBrakeForce =9999;
int front_dist = 4000;
int RFF_1 = 70 ;
int RFF_2 = 85;
//int RFF_3 = 0;
int RBF = 40;
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
bool brake = 0;
bool brakeF = 0;
bool LS = 0;
bool RS = 0;
bool FS = 0;


float nowSpeed = 0;

String fileName = "";

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void loop() {
//  gyroBack();
//  SerialEvent();
  if (digitalRead(A4)==1&&digitalRead(A5)==1) gyroFront();
//  SerialEvent();
  light();
  SerialEvent();
  forceCaculate();
//  delay(500);
  if (digitalRead(A2)) digitalWrite(A0,0);
  else digitalWrite(A0,1);

}
