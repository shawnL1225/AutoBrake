 #include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial Serial4(10,11);//(RX,TX)
Servo S1;

char incomingByte;
String incomeString=" ";
int VGALED;

void setup()
{ 
  Serial.begin(9600);
  Serial4.begin(9600);
  Serial4.print("");
  Serial.println("\nTransmission begin");
  
  // ---------Servo--------------
  S1.attach(8);
  S2.attach(9);
  S1.write(0);
  S2.write(0);
  // ---------declare--------------
  pinMode (2,INPUT);
  pinMode (VGALED,OUTPUT);
  digitalWrite(VGALED,0);
  delay(100);
  digitalWrite(VGALED,1);
  delay(100);
  digitalWrite(VGALED,0);
} 
void loop() {
  serialEvent();
}
