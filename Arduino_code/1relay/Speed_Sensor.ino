void speedSensor(){
  //----------------------------if dectect-------------------------------
  botton= digitalRead(7);
  magnet= digitalRead(8);
    
  Serial.print(ms-lms);
  rms=millis();
  if (botton==0&&lbotton!=0){
    ms=millis();
    ts=ms-lms;
    sv=66.04/2/*tire radious*/*360/16/ts;
    hv=sv/3.6;
    lms=ms;
  }
  if (rms-lms>1000){
    ts=ms-lms;
    lms=rms;
    sv=hv=0;
//    Serial.println("Speed : 0.0km/hr");
  }
  if(magnet==0&&lmagnet!=0){
    homs = millis();
    gms = homs-lhoms;
    int sv1 = 66.04/2*360/gms;
    hv1 = sv1/3.6;
    lhoms=homs;
  }
  if (1){
//  if (lhv!=hv){//-------------show value------------------------------
    Serial.print(ts);
    Serial.print(" ms");
    Serial.print("  \t");
    Serial.print(hv);
    Serial.print(" km/hr ");
    Serial.println("\t");
//    Serial.print(gms);
//    Serial.print(" ms");
//    Serial.print("  \t");
//    Serial.print(hv1);
//    Serial.println(" km/hr ");
    String SDs =String(ts) + " ms"+"  \t"+ /*sv+" m/s""\t"*/ String(hv) + " km/hr ";
    lhv=hv;
  }
  lbotton = botton;
//  lmagnet = magnet;
}
