#include <SoftwareSerial.h>
SoftwareSerial TOF(2, 3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  TOF.begin(9600);
  TOF.setTimeout(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  float Distance = 0;
  if (TOF.available() > 0){
    if (TOF.parseFloat() < 50.0){
      Distance = TOF.parseFloat();
    }
    Serial.print("Distance:");
    Serial.println(Distance);
  }

}
