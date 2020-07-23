void battery(){
  if ((CTRLP<=1&&millis()-lbsms>3000)||lbsms==0){
    double batteryV=(analogRead(A4)+analogRead(A5)+analogRead(A6))*25/1024.0;
    Serial.print("Battery Voltage = ");
    Serial.print(batteryV/100.00);
    Serial.println(" V");
    int percentage=map(batteryV,4600,5400,0,100);
    String sendS = 'B'+String(percentage)+' ';
    Serial4.print(sendS);
    lbsms=millis();
  }
}
