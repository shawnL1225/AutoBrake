
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
    double hv;
    if (abs(hv1-hv2)<1) hv =(hv1+hv2)/2.00;
    if (abs(hv-lhv)<5){
      String v = String (int (hv*100));
      String sendM= '@' + b+v;
      Serial.println(sendM);
      Serial4.print(sendM);
    }
    lrms=rms;
    lhv=hv;
  }
}
