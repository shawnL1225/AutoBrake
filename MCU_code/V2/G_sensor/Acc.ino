void acc(){
  sensors_event_t a, g, temp;
  mpu6050.getEvent(&a, &g, &temp);
 
//   Print out the values 
  ax = a.acceleration.x + fixax;
  ay = a.acceleration.y + fixay;
  az = a.acceleration.z + fixaz;

  
}
