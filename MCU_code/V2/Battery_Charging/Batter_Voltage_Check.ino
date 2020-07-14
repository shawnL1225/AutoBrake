void BVC(double BV){
  screen.setFont(&FreeSans12pt7b);
  screen.setTextSize(2);
  Serial.print("Battery Voltage:");
  Serial.print(BV);
  Serial.print(" V\t");
  int per = ((BV-11.4)*100/2.1+0.5);
  Serial.print((BV-11.4)*100/2.1);
  if (per==100) screen.setCursor(3,48);
  else if(per>=10) screen.setCursor(17,48);
  else if (per<10) screen.setCursor(35,48);
  screen.print(per);
  Serial.println(" %");
  screen.println("%");
  screen.display();
}
