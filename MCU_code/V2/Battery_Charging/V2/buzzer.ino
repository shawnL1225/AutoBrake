void buzzer(short frequency,short buzzetime){
  for(short i=0; i<buzzetime;i++){
    tone (6,frequency);
    delay(100);
    analogWrite(6,0);
  }
}
