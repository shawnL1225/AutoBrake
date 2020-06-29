void battery(){
//  Serial.println(analogRead(A5));
  int batteryV =map(analogRead(A5),0,1023,0,1500);
  String BV="Battery :"+String(batteryV/100.00)+" V";
  if (lBV!=BV) SDWrite(BV);
  lBV=BV;
  int percentage=map(batteryV,1050,1350,0,100);
  lcd.setCursor(13,0);
  lcd.print(percentage);
  lcd.print('%');
  String BpercentageS=String(percentage);
  Serial.println(BV);
  Serial1.write('B');
  for (int i=0; i<BpercentageS.length();i++) 
    Serial1.write(BpercentageS[i]);//percentage of battery
  Serial1.write('|');
}
