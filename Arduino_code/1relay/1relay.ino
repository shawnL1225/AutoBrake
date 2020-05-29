#include <SoftwareSerial.h>
SoftwareSerial Serial4(10,11);//(RX,TX)

char incomingByte;
String incomeString=" ";
double ts,sv,hv=0,hv1=0,lhv;
unsigned long lrms,rms,ms,homs,lhoms,gms,lms=ms=homs=lhoms=0;
bool botton, lbotton, magnet, lmagnet; //value for speed sensor
int batteryV;

void setup(){ 
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.setTimeout(50);
  Serial4.write("");
  Serial.println("\nTransmission begin");
}

void loop() {

  speedSensor();
  battery();
  
  rms=millis();
  if (rms-lrms>150){
    serialEvent();
  }

  

}
