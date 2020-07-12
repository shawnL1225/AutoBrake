void ultra_ToF(){
  if (TOF.available()){
    tof_distance = TOF.parseFloat();
  }
  digitalWrite(trigPin, LOW); //31 echo pin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    // 讀取 EchoPin LOW->HIGH->LOW 的這段時間是多少 us unsigned 
  ultra_duration = pulseIn(echoPin, HIGH); 
    // 換算成距離
  IR_ave_distance_cm = ultra_duration/58; 
}
