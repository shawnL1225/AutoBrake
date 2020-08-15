void send(){
//  Serial.print("Acc X: ");
//  Serial.print(ax);
//  Serial4.print("A");
//  Serial4.print(ax);
//  Serial4.print(' ');
//  Serial.print("   Acc Y: ");
//  Serial.print(ay);
//  Serial.print("   Acc Z: ");
//  Serial.print(az);
//  Serial.println(" m/s^2");
  
//  Serial.print("AngleX= ");
//  Serial.print(dx);
//  Serial4.print("I");
//  Serial4.print(dx);
//  Serial4.print(' ');
//  Serial.print("   AngleY= ");
//  Serial.print(dy);
//  Serial4.print("G");
//  Serial4.print(dy);
//  Serial4.print(' ');
//  Serial.print("   AngleZ= ");
//  Serial.println(dz);

  
//  Serial.print("Humidity: ");
//  Serial.print(h);
//  Serial.print("%\t");
//  Serial4.print("h");
//  Serial4.print(h);
//  Serial4.print(' ');


//  Serial.print("Celsius: ");
//  Serial.print(t);
 if (distanceB>10&&distanceB<1000){
    Serial4.print("C d");
    Serial4.println(distanceB);
    Serial4.flush();
    Serial.print("C d");
    Serial.print(distanceB);
  }
  Serial.print(distanceB);
  Serial.print("t");
  Serial.print(t);
  Serial4.print("t");
  Serial4.println(t);
  Serial4.flush();
//  Serial.println("*C\t");
//  Serial.print("distanceB:");
//  Serial.println(distanceB);
  
  
  

  Serial.println("--------------------------------");

  delay(100);
}
