#include <SoftwareSerial.h>

SoftwareSerial Serial4(A0,A1);

int autoBMax=290, autoBMin=150, autoBMaxF=100, autoBMinF=0; // analog200 -> softbrake  
int manualBMax=396, manualBMin=251, manualBMaxF=100, manualBMinF=0;
int autoBF = 0, manualBF = 0, TbrakeF = 0;
int requestForce = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  brakeS();
  brakeA();
  SerialEvent();
}
