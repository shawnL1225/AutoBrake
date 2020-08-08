#include <SoftwareSerial.h>

SoftwareSerial Serial4(A0,A1);

int autoBMax=723, autoBMin=50, autoBMaxF=650, autoBMinF=0;
int manualBMax=723, manualBMin=50, manualBMaxF=650, manualBMinF=0;
int autoBF = 0, manualBF = 0, TbrakeF = 0;
int requestForce = 100;

void setup() {
  Serial.begin(9600);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
//  pinMode(5,OUTPUT);
//  pinMode(6,OUTPUT);
}

void loop() {
  brakeS();
  brakeA();
  SerialEvent();
}
