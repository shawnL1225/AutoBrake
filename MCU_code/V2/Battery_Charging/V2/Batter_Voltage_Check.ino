void BVC(double BV){
  Serial.print("Battery Voltage:");
  Serial.print(BV);
  Serial.print(" V\t");
  short per = ((BV-11.4)*100/2.1+0.5);
  Serial.print((BV-11.4)*100/2.1);
  Serial.println(" %");
}
