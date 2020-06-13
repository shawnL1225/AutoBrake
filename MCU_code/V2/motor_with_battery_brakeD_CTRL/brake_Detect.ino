void brakeDetect(){
  int brakeV = analogRead(A1);
  if (brakeV<300) brake =1;
  else if (brakeV>=300) brake=0;
}
