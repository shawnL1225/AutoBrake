#include <SoftwareSerial.h>
#include <SharpIR.h>

#define IR80_1P A0
#define IR80_2P A1
#define model80 1080
#define IR150P A2
#define model150 20150

#define ultraLTP 8
#define ultraLEP 9
#define ultraMTP 6
#define ultraMEP 7
#define ultraRTP 4
#define ultraREP 5

SoftwareSerial Mother(10,11);

SharpIR IR80_1 = SharpIR(IR80_1P, model80);
SharpIR IR80_2 = SharpIR(IR80_2P, model80);
SharpIR IR150 = SharpIR(IR150P, model150);

double IRD80_1,IRD80_2,IRD150;
double ultraLD,ultraMD,ultraRD;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  IR();
  ultra();
  String printS = String(ultraLD) + "cm  \t" + String(ultraMD) + "cm  \t" + String(ultraRD) + "cm  \n" + String(IRD80_1) + "cm  \t" + String(IRD150) + "cm  \t"  + String(IRD80_2) + "cm  \t" ;
  Serial.println(printS);
  Serial.println("----------------------------------------");
  delay(100);
}
