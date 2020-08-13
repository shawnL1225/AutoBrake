#include <SoftwareSerial.h>

bool DirectIn = 0;
bool RBlink = 0;
bool LBlink = 0;
bool BBlink = 0;

int autoBMax=737, autoBMin=547, autoBMaxF=100, autoBMinF=0; // analog200 -> softbrake  
int manualBMax=396, manualBMin=251, manualBMaxF=100, manualBMinF=0;
int autoBF = 0, manualBF = 0, TbrakeF = 0;
int requestForce = 1;

void setup() {
  Serial.begin(9600);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.println("\nSetup OK");
}

void loop() {
  brakeS();
  brakeA();
  SerialEvent();
}
