void battery(){
  if ((ASPXpower<95&&millis()-lbsms>3000)||lbsms==0){
    int batteryV =map(analogRead(A2),0,1023,0,1500);
    Serial.print("Battery Voltage = ");
    Serial.print(batteryV/100.00);
    Serial.println(" V");
    String sendS = 'V'+String(batteryV)+' ';
    Serial4.print(sendS);
    lbsms=millis();
  }
}
