void battery(){
  if ((CTRLP<=1&&millis()-lbsms>3000)||lbsms==0){
    (void)analogRead(A3);
    delay(10);
    double batteryV=analogRead(A3)*5*11.08583690987124/1023;
    Serial.print("Battery Voltage = ");
    Serial.print(batteryV/100.00);
    Serial.println(" V");
    int percentage=map(batteryV,4600,5400,0,100);
    if (percentage < 100) BOK = 0;
    else BOK = 1;
    String sendS = 'B'+String(percentage)+' ';
    Serial4.print(sendS);
    lbsms=millis();
  }
}
