void speed (){
  //Speed over limited speed
  if (nowSpeed > maxSpeed) digitalWrite(7,1);
  else digitalWrite(7,0);
}
