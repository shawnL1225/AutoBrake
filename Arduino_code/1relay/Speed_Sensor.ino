void speedSensor(){
//----------------------------if dectect-------------------------------
  magnet1= digitalRead(7);
  magnet2= digitalRead(8);
  
//  Serial.print(ms-lms);
  rms=millis();
  if (magnet1==0&&lmagnet1!=0){
    ms1=millis();
    ts1=ms1-lms1;
    sv1=66.04/2*360/ts1;
    hv1=sv1*0.36;
    lms1=ms1;
  }
  if (rms-lms1>4000){
    ts1=ms1-lms1;
    lms1=rms;
    sv1=hv1=0;
//    Serial.println("Speed : 0.0km/hr");
  }
  if(magnet2==0&&lmagnet2!=0){
    ms2 = millis();
    ts2 = ms2-lms2;
    sv2=66.04/2*360/ts2;
    hv2=sv2*0.36;
    lms2=ms2;
  }
  if (rms-lms2>4000){
    ts2=ms2-lms2;
    lms2=rms;
    sv2=hv2=0;
//    Serial.println("Speed : 0.0km/hr");
  }

  if (1){
    if ((hv2!=lhv2)||(hv1!=lhv1)){//-------------show value------------------------------
      Serial.print(magnet1);
      Serial.print(" | ");
      Serial.print(ts1);
      Serial.print(" ms");
      Serial.print("  \t");
      Serial.print(hv1); 
      Serial.print(" km/hr ");
      Serial.print("\t");
      Serial.print(magnet2);
      Serial.print(" ");
      Serial.print(ts2);
      Serial.print(" ms");
      Serial.print("  \t");
      Serial.print(hv2); 
      Serial.println(" km/hr ");
  //    String SDs =String(ts) + " ms"+"  \t"+ /*sv+" m/s""\t"*/ String(hv) + " km/hr ";
      
    }
  }
  lhv2=hv2;
  lhv1=hv1;
  lmagnet1 = magnet1;
  lmagnet2 = magnet2;
}
