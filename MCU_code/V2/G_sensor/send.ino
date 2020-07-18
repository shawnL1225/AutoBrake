void send(){
  Serial.print("Acc X: ");
  Serial.print(ax);
  Serial4.print("A");
  Serial4.print(ax);
  Serial.print("   Acc Y: ");
  Serial.print(ay);
  Serial.print("   Acc Z: ");
  Serial.print(az);
  Serial.println(" m/s^2");


  Serial.print("AngleX= ");
  Serial.print(dx);
  Serial4.print("I");
  Serial4.print(dx);
  Serial.print("   AngleY= ");
  Serial.print(dy);
  Serial4.print("G");
  Serial4.print(dy);
  Serial.print("   AngleZ= ");
  Serial.println(dz);

  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial4.print("h");
  Serial4.print(h);
  Serial.print("Celsius: ");
  Serial.print(t);
  Serial4.print("t");
  Serial4.print(t);
  Serial.println("*C\t");

  Serial.println("--------------------------------");

  delay(500);
}
