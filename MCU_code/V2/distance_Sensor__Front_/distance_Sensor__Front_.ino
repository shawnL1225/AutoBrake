#include <SoftwareSerial.h>
#include <SharpIR.h>

#define IRPin1 A0
#define IRPin2 A1
#define trigPin 4
#define echoPin 5
#define model 100500

SoftwareSerial Serial4(10,11);
SoftwareSerial Serial5(8,9);
SharpIR mySensor1 = SharpIR(IRPin1, model);
SharpIR mySensor2 = SharpIR(IRPin2, model);

int distance_cm_1, distance_cm_2;
int dou_distance_cm, ave_distance_cm;

double ultraDistance;
double IR40D,finalV;

long duration;

void setup() {
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial5.begin(9600);
  Serial.println("begin");
}

void loop() {
  dS();
}
