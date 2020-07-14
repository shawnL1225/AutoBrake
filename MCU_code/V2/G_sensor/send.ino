void send(){
  Serial.print("Acc X: ");
  Serial.print(ax);
  Serial.print("   Acc Y: ");
  Serial.print(ay);
  Serial.print("   Acc Z: ");
  Serial.print(az);
  Serial.println(" m/s^2");

  Serial.print("AngleX= ");
  Serial.print(dx);
  Serial.print("   AngleY= ");
  Serial.print(dy);
  Serial.print("   AngleZ= ");
  Serial.println(dz);
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Celsius: ");
  Serial.print(t);
  Serial.println("*C\t");

  Serial.println("--------------------------------");

  delay(500);
}
