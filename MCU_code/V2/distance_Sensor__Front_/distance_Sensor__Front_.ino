#include <SoftwareSerial.h>
#include <SharpIR.h>

#define IRPin1 A0
#define IRPin2 A1
#define model 100500
#define trigPin 4
#define echoPin 5
#define condPin 12


SoftwareSerial TOF (8,9);
SoftwareSerial Mother (10,11);

SharpIR mySensor1 = SharpIR(IRPin1, model);
SharpIR mySensor2 = SharpIR(IRPin2, model);

int IR_distance_cm_1, IR_distance_cm_2;
int ultra_duration;

double ultra_distance; 
double IR_dou_distance_cm, IR_ave_distance_cm;
double tof_distance;
double finalV;


void setup() {
  Serial.begin(9600);
  TOF.begin(9600);
  Mother.begin(9600);
  pinMode(condPin,OUTPUT);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  digitalWrite(condPin,1);
  Serial.println("Begin");
  
}

void loop() {
  IR();
}
