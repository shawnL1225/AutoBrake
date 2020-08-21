#include <SoftwareSerial.h>

bool DirectIn = 0;
bool RBlink = 0;
bool LBlink = 0;
bool BLight = 0;
bool Bstatus = 0;

int autoBMax=800, autoBMin=200, autoBMaxF=100, autoBMinF=0; // analog200 -> softbrake  
int manualBMax=322, manualBMin=198, manualBMaxF=100, manualBMinF=0;
int autoBF = 0, manualBF = 0, TbrakeF = 0;
int requestForce = 1;

unsigned long Btime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.println("\nSetup OK");
}

void loop() {
  brakeS();
  brakeA();
  SerialEvent();
  light();
}
