
void serialEvent(){
  //------------ Receive ------------------
  if (1){ //Serial4 Receive
    if(Serial4.available()) {
      if(Serial4.read()=='@') {
          int n = Serial4.parseInt();
      }
    }
  }

  //----------------- Write ----------------------
  if (1){
    String b =' '+String (batteryV)+"\b"+' ';
    String h = String (int (hv*100));
    String a = String (int (hv1*100));
    String sendM= '@' + b+h+' '+a;
//    Serial.println(sendM);
    Serial4.print(sendM);
    lrms=rms;
  }
}
