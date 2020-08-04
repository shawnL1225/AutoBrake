void ultra(){
  digitalWrite(TP, LOW); 
  delayMicroseconds(2);
  digitalWrite(TP, HIGH);
  delayMicroseconds(10);
  digitalWrite(TP, LOW);
  double duration = pulseIn(EP, HIGH); 
    // 換算成距離
  distanceB = duration/58; 
  
}
