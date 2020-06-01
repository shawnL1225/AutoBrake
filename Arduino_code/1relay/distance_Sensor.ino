void dS(){
  for(char i=0;i<5;i++) {
//    Serial.println("*************");
    distance_cm_1 = mySensor1.distance();
    distance_cm_2 = mySensor2.distance();
    distance_cm_1 = distance_cm_1*1.12;
    distance_cm_2 = distance_cm_2*1.12;
    dou_distance_cm = distance_cm_1+distance_cm_2;
    dou_distance_cm = dou_distance_cm /2;
    ave_distance_cm = ave_distance_cm + dou_distance_cm;                
   }
  ave_distance_cm /= 5;

  if (ultraDistance<100) finalV = ultraDistance;
  else finalV = ave_distance_cm;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  ultraDistance= duration*0.034/2;
  
  // Prints the distance on the Serial Monitor
  if (1){
    Serial.print("Sensor1: ");
    Serial.print(distance_cm_1);
    Serial.print(" cm");
    Serial.print("\tSensor2: ");
    Serial.print(distance_cm_2);
    Serial.print("cm");
    Serial.print("\tDouble_Sensor: ");
    Serial.print(dou_distance_cm);
    Serial.print("cm");
    Serial.print("\tAve_Mean distance: ");
    Serial.print(ave_distance_cm);
    Serial.print("cm");                     
    ave_distance_cm = 0;
    Serial.print("\tUltra Distance: ");
    Serial.print(ultraDistance);
    Serial.print("\tFinal  ");
    Serial.println(finalV);
    delay(50);
  }
}
