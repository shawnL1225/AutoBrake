void speedSensor(){
  rms = millis();
//----------------------------if dectect-------------------------------
  magnet1= digitalRead(7);
  magnet2= digitalRead(8);
//----------------------turn first sensor value------------------------
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
  }
  
//----------------------turn second sensor value------------------------
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
  }
  else if (ms1==0){
    sv1=hv1=0;
  }
  else if (ms2==0){
    sv2=hv2=0;
  }

//------------------------show all value----------------------------
  if (1){
    if ((hv2!=lhv2)||(hv1!=lhv1)){
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
//      String SDs =String(ts) + " ms"+"  \t"+ /*sv+" m/s""\t"*/ String(hv) + " km/hr ";
    }
  }

//----------------------mix two sensor value------------------------
  if (abs(hv1-hv2)<1) fhv =(hv1+hv2)/2.00;
  else errt++;
//--------------show fianl value & send value-----------------------
  if (hv1==0&&hv2==0&&hv1!=printed){
    Serial.print("V0");
    Serial4.print("V0");
    printed=0;
  }
  if (abs(fhv-lfhv)<5&&fhv!=lfhv&&(fhv!=printed)){
    String sendV= 'V'+ String (int (fhv*100));
    Serial.println(sendV);
    Serial4.print(sendV);
    errt=0;
    printed=fhv;
    errt=9000;
  }
  
  if (errt>10000) {
    Serial.println("Error Occur");
    Serial4.print("E ");
    errt=0;
  }
//-------------------------last value modify------------------------
  lhv2=hv2;
  lhv1=hv1;
  lmagnet1 = magnet1;
  lmagnet2 = magnet2;
}
