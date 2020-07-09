void battery(){
//  Serial.println(analogRead(A5));
  int Vin = analogRead(A5);
  double batteryV=Vin*25/1024.0;
  String BV="Battery :"+String(batteryV/100.00)+" V"; 
  lBV=BV;
  int percentage=map(batteryV,1050,1350,0,100);
  lcd.setCursor(13,0);
  lcd.print(percentage);
  lcd.print('%');
  String BpercentageS=String(percentage);
//  Serial.println(BV);
  Serial1.write('B');
  for (int i=0; i<BpercentageS.length();i++) 
    Serial1.write(BpercentageS[i]);//percentage of battery
  Serial1.write('|');
}
