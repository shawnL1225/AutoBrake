void show(){
  // Prints the distance on the Serial Monitor
  if (1){
    if (ultra_distance<100) finalV = ultra_distance;
    else if (tof_distance>500) finalV = tof_distance;
    else finalV = IR_ave_distance_cm;
    Serial.print("Sensor1: ");
    Serial.print(IR_distance_cm_1);
    Serial.print(" cm");
    Serial.print("\tSensor2: ");
    Serial.print(IR_distance_cm_2);
    Serial.print("cm");
    Serial.print("\tDouble_Sensor: ");
    Serial.print(IR_dou_distance_cm);
    Serial.print("cm");
    Serial.print("\tAve_Mean distance: ");
    Serial.print(IR_ave_distance_cm);
    Serial.print("cm");                     
    Serial.print("\tUltra Distance: ");
    Serial.print(ultra_distance);
    Serial.print("\tFinal  ");
    Serial.println(finalV);
    IR_ave_distance_cm = 0;
  }
}
