void battery(){
  if ((CTRLP<=1&&millis()-lbsms>3000)||lbsms==0){
    int batteryV =map(analogRead(A2),0,1023,0,1500);
    Serial.print("Battery Voltage = ");
    Serial.print(batteryV/100.00);
    Serial.println(" B");
    String sendS = 'B'+String(batteryV)+' ';
    Serial4.print(sendS);
    lbsms=millis();
  }
}
