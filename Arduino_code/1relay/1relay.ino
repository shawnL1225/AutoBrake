#include <SoftwareSerial.h>
SoftwareSerial Serial4(10,11);//(RX,TX)

bool magnet1=1,magnet2=1,lmagnet1,lmagnet2;
unsigned long rms,lrms,ms1,lms1,ms2,lms2;
unsigned int ts1,ts2,sv1,sv2;
double hv1,lhv1,hv2,lhv2,lhv;
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
