
void serialEvent(){
  //------------ Receive ------------------
  if (1){ //Serial4 Receive
    if(Serial4.available()) {
      char in = Serial4.read();
      if(in=='@') {
          int n = Serial4.parseInt();
      }
      else if (in=='B'){
        String sendB ='B'+String (batteryV);
        Serial.println(sendB);
        Serial4.print(sendB);
      }
    }
  }

  //----------------- Write ----------------------
  if (1){
  //Speed
    double hv;
//    if (abs(hv1-hv2)<1) hv =(hv1+hv2)/2.00;
    if (abs(hv-lhv)<5){
      hv=hv1;
      String sendV= 'V'+ String (int (hv*100));
      Serial.println(sendV);
      Serial4.print(sendV);
    }
    lrms=rms;
    lhv=hv;
  }
}
