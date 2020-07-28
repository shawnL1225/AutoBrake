#include <SoftwareSerial.h>
#include <SharpIR.h>

#define IR80_1P A1
#define IR80_2P A2
#define model80 1080

#define ultraLTP 3
#define ultraLEP 2
#define ultraMTP 8
#define ultraMEP 7
#define ultraRTP 12
#define ultraREP 11

SoftwareSerial Serial4(4,5);

SharpIR IR80_1 = SharpIR(IR80_1P, model80);
SharpIR IR80_2 = SharpIR(IR80_2P, model80);

double IRD80_1,IRD80_2;
double ultraLD,ultraMD,ultraRD;

double soundSpeed=58.0;

unsigned long trigger_time=0;

bool BIRD80_1 = 0,BIRD80_2 = 0,BultraLD = 0,BultraMD = 0,BultraRD = 0;
bool Serial4required = 0;

void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  pinMode(ultraLTP,OUTPUT);
  pinMode(ultraMTP,OUTPUT);
  pinMode(ultraRTP,OUTPUT);
  digitalWrite(9,1);
  pinMode(ultraLEP,INPUT);
  pinMode(ultraMEP,INPUT);
  pinMode(ultraREP,INPUT);
  pinMode(IR80_1P,INPUT);
  pinMode(IR80_2P,INPUT);
}

void loop() {
  IR();
  ultra();
  show();
  detect();
}
