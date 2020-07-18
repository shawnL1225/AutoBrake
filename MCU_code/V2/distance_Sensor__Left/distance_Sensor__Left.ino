#include <SoftwareSerial.h>
#include <SharpIR.h>

#define IR80_1P A0
#define IR80_2P A1
#define model80 1080

#define ultraLTP 8
#define ultraLEP 9
#define ultraMTP 6
#define ultraMEP 7
#define ultraRTP 4
#define ultraREP 5

SoftwareSerial Serial4(10,11);

SharpIR IR80_1 = SharpIR(IR80_1P, model80);
SharpIR IR80_2 = SharpIR(IR80_2P, model80);

double IRD80_1,IRD80_2;
double ultraLD,ultraMD,ultraRD;

double soundSpeed=58.0;

unsigned long trigger_time=0;

bool BIRD80_1 = 0,BIRD80_2 = 0,BultraLD = 0,BultraMD = 0,BultraRD = 0;

void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
}

void loop() {
  IR();
  ultra();
  show();
  detect();
}
