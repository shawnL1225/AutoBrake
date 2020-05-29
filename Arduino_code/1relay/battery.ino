
void battery(){
  Serial.println(analogRead(A5));
  batteryV =map(analogRead(A5),0,1023,0,1500);
}
