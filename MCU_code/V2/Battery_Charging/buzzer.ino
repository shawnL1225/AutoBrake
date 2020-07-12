void buzzer(int frequency,int buzzetime){
  for(int i=0; i<buzzetime;i++){
    analogWrite(6,frequency);
    delay(100);
    analogWrite(6,0);
  }
}
