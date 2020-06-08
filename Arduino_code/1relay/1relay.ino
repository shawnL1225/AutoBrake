#include <SoftwareSerial.h>
#include <SharpIR.h>

#define IRPin1 A0
#define IRPin2 A1
#define trigPin 4
#define echoPin 5
#define model 100500

SoftwareSerial Serial4(10,11);//(RX,TX)
SharpIR mySensor1 = SharpIR(IRPin1, model);
SharpIR mySensor2 = SharpIR(IRPin2, model);

int distance_cm_1, distance_cm_2;
int dou_distance_cm, ave_distance_cm;
int batteryV;

bool magnet1=1,magnet2=1,lmagnet1,lmagnet2;
long duration;
unsigned long rms,lrms,ms1,lms1,ms2,lms2;
unsigned int ts1,ts2,sv1,sv2;
double hv1,lhv1,hv2,lhv2,lhv;
double ultraDistance, finalV;


void setup(){ 
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.setTimeout(50);
  Serial.println("\nTransmission begin");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,1);
  pinMode(8,OUTPUT);
  digitalWrite(8,1);
}

void loop() {

  speedSensor();
  battery();
  
  rms=millis();
  if (rms-lrms>150){
    serialEvent();
    dS();
  }
  
  

}
