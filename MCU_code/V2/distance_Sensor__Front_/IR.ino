void IR(){
  for(char i=0;i<3;i++) {
//    Serial.println("*************");
    IR_distance_cm_1 = mySensor1.distance();
    IR_distance_cm_2 = mySensor2.distance();
    IR_distance_cm_1 = IR_distance_cm_1*1.12;
    IR_distance_cm_2 = IR_distance_cm_2*1.12;
    IR_dou_distance_cm = IR_distance_cm_1+IR_distance_cm_2;
    IR_dou_distance_cm = IR_dou_distance_cm /2;
    IR_ave_distance_cm = IR_ave_distance_cm + IR_dou_distance_cm;                
   }
  IR_ave_distance_cm /= 3;
}
