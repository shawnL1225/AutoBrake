void motor ( int SPXpower, float nowSpeed, bool brake){

  //make sure value don't raise sharply by accident & Let value be above 93
    if ((SPXpower-LSPXpower)>=60||SPXpower<91) err=1;
    else err=0;

  //Tell the condition if error occur
    if (err&&!lerr) {
      Serial.println("CTRL　ERROR OCCUR");
      Serial4.print("E ");
      SPX(94);
      ASPXpower=94;
      Serial.println("BREAK STOP");
      lerr=err;
      delay(100);
    }
    else if (!err&&lerr){
      Serial.println("Error Solved");
      Serial4.print("S ");
      lerr=err;
    }

  //Activate the motor
  //STOP the motor
    if ((SPXpower==92||SPXpower==93||SPXpower==94)&&(LASPXpower==92||LASPXpower==93||LASPXpower==94)){
      //motor Stopped
      ASPXpower = SPXpower;
      SPX(ASPXpower);
    }
    else if ((SPXpower==92||SPXpower==93||SPXpower==94)&&(LASPXpower!=92&&LASPXpower!=93&&LASPXpower!=94)){
      //motor Stop
      ASPXpower=SPXpower;
      SPX(ASPXpower);
      Serial4.print('P');
      Serial4.print(ASPXpower);
      Serial4.print(' ');
      Serial.println("BREAK STOP");
    }
    else if (brake==1){
      SPX(94);
      ASPXpower=94;
      Serial.println("BREAK STOP");
      Serial4.print("P94 ");
    }
      
  //ACCELERATION NEGATIVE
    else if (SPXpower<LASPXpower){
      if(!err){
        for(int degree=LASPXpower ; (SPXpower<=degree&&(SPXpower>=94)&&appStart) ; degree--){
          int changedValueFromController = map(analogRead(A1),180,880,93,145);
          if (changedValueFromController >= degree) break;
          SPX(degree);
          if (degree==95) delay(50); 
          else delay (MBR/3);
          ASPXpower=degree;
          if (!brake) {
              Serial4.write('P');
              Serial4.print(ASPXpower);
              Serial4.write(' ');
          }
        }
      }
    }

  //Speed under limited speed
    if (nowSpeed < maxSpeed){
    //ACCELERATION POSITIVE
      if (SPXpower>LASPXpower&&!err&&!brake&&appStart){
        for(int degree=LASPXpower ; (SPXpower>=degree&&(SPXpower>=94)&&appStart) ; degree++){
          int changedValueFromController = map(analogRead(A1),180,880,93,145);
          if (changedValueFromController <=degree||hv>maxSpeed) break;
          SPX(degree);
          if (ost=0) ost=1;
          if (degree==94) delay(50);
          else delay (MBR*ost);
          ASPXpower=degree;
          if (!brake) {
            Serial4.write('P');
            Serial4.print(ASPXpower);
            Serial4.write(' ');
          }
        }
      }
      ost=0;
    }

  //Speed equal limited speed
     else if (int(nowSpeed)==maxSpeed&&SPXpower!=92&&SPXpower!=93&&SPXpower!=94&&appStart){
       if(SPXpower>=LASPXpower){
         ASPXpower=LASPXpower;
         SPX(ASPXpower);
         ost=1;
         if (!err&&!brake) {
            Serial4.write('P');
            Serial4.print(ASPXpower);
            Serial4.write(' ');
           }
         }
       }


  //Speed over limited speed
     else if (nowSpeed > maxSpeed){
       if (SPXpower>=LASPXpower){
         if (SPXpower!=92&&SPXpower!=93&&SPXpower!=94&&!err&&!brake&&appStart){
           int check = nowSpeed-maxSpeed+0.5;
           ASPXpower =SPXpower-check*2-ost*2;
           if (ASPXpower>LASPXpower){
             ASPXpower=LASPXpower;
           }
           ost++;
           if (ASPXpower<92) ASPXpower=93;
           SPX(ASPXpower);
           delay(100);
           if (!brake) {
             Serial4.write('P');
             Serial4.print(ASPXpower);
             Serial4.write(' ');
           }
         }
       }
     }

  //Tell the condition
    if(SPXpower!=LSPXpower||ASPXpower!=LASPXpower){
      if (!err){
        String SDSPX = "("+String(SPXpower)+","+String(LSPXpower)+","+String(ASPXpower)+","+String(LASPXpower)+","+String(nowSpeed)+","+String(maxSpeed)+","+String(brake)+")\t";
        Serial.print(SDSPX);
        if (!appStart){
            Serial.println("Bike LOCK");
        }
        else if ((ASPXpower==92||ASPXpower==93||ASPXpower==94)&&(LASPXpower==92||LASPXpower==93||LASPXpower==94)){
          Serial.println("BREAK STOPPED ");
        }
        else if ((ASPXpower==92||ASPXpower==93||ASPXpower==94)&&(LASPXpower!=92||LASPXpower!=93&&LASPXpower!=94)){
          Serial.println("BREAK STOPPING ");
        }
        else if (ASPXpower>=95&&ASPXpower<=141){
          Serial.println("FORWARD     ");
        }
        else if (ASPXpower>=142&&ASPXpower<=179){
          Serial.println("MAX FORWARD ");
        }
      } 
    }

  //Edit value of LASPXpower & LSPXpower
    LASPXpower = ASPXpower;
    LSPXpower = SPXpower;
}

void SPX(int power){
  if (power<=94) power=94;
  else if (power>=142) power=142;
  int var = map (power,94,142,0,255);
//  Serial.print(var);
  analogWrite(3,var);
}
