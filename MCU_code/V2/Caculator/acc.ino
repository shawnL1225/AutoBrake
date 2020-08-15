void acc(){
  sensors_event_t a, g, temp;
  mpu6050.getEvent(&a, &g, &temp);
 
//   Print out the values
  ax = a.acceleration.x + fixax;
  ay = a.acceleration.y + fixay;
  double az = a.acceleration.z + fixaz;
  Serial.print("A x: ");
  Serial.print(ax);
  Serial.print(" y : ");
  Serial.print(ay);
  Serial.print(" z : ");
  Serial.println(az);
}
