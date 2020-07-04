int t;
void motor ( int SPXpower, float nowSpeed, bool brake){
   String htc; //how motor value change
   
   //make sure value don't raise sharply by accident & Let value be above 93
      if ((SPXpower-LSPXpower)>=60||SPXpower<91) err=1;
      else err=0;
      
   //Tell the condition if error occur
      if (err&&!lerr) { //Only print once, could be unlock only by cellphone app
        Serial.println("ERROR OCCUR");
        SDWrite("ERROR OCCUR  ");
        SPX(94);
        ASPXpower=94;
        Serial.println("BREAK STOP  ");
        SDWrite("BREAK STOP  ");
        lerr=err;
      }
      else if (!err&&lerr){
        Serial.println("Error Solved");
        SDWrite("Error Solved");
        lcd.setCursor(0,0);
        lcd.print("0%         ");
        lerr=err;
      }
 
   //Activate the motor
   //STOP the motor
     if ((SPXpower==92||SPXpower==93||SPXpower==94)&&(LASPXpower==92||LASPXpower==93||LASPXpower==94)){
       //motor dead lock
       ASPXpower= SPXpower;
       SPX(ASPXpower);
     }
     else if ((SPXpower==92||SPXpower==93||SPXpower==94)&&(LASPXpower!=92&&LASPXpower!=93&&LASPXpower!=94)){
       //motor dead lock free
       SPX(3);
       delay(30);
       ASPXpower=SPXpower;
       SPX(ASPXpower);
       Serial1.print("M0|");
     }
     else if (brake==1){
       if (LASPXpower!=92&&LASPXpower!=93&&LASPXpower!=94){
         SPX(3);
         delay(300);
         htc+="3 ";
       }
       SPX(94);
       ASPXpower=94;
       htc+="94";
     }
     
   //ACCELERATION NEGATIVE
     else if (SPXpower<LASPXpower){
       if(!err){
         for(int degree=LASPXpower ; (SPXpower<=degree&&(SPXpower>=94)&&appStart) ; degree--){
           int changedValueFromController = map(analogRead(A0),180,880,93,145);
           if (changedValueFromController >= degree) break;
           htc=htc+degree+"　";
           SPX(degree);
           if (degree==95) delay(50); 
           else delay (MBR/3);
           ASPXpower=degree;
           if (!brake) {
             lcd.setCursor(0,0);
             if ((degree-94)<0) RASPXpowerp=0;
             else RASPXpowerp=(degree-94)*100/51;
             lcd.print(RASPXpowerp);
             lcd.print("%       ");
             t++;
             if (t>2){
               String RASPXpowerpS = String (RASPXpowerp);
               Serial1.write('M');
               for(int i=0; i<RASPXpowerpS.length();i++)
                  Serial1.write(RASPXpowerpS[i]);
               Serial1.write('|');
               t=0;
             }
           }
         }
         Serial1.write('M');
         String RASPXpowerpS = String (RASPXpowerp);
         for(int i=0; i<RASPXpowerpS.length();i++)
            Serial1.write(RASPXpowerpS[i]);
         Serial1.write('|');
         t=0;
       }
     }

   //Speed under limited speed
      if (nowSpeed < maxSpeed){
      //ACCELERATION POSITIVE
        if (SPXpower>LASPXpower&&!err&&!brake&&appStart){
          for(int degree=LASPXpower ; (SPXpower>=degree&&(SPXpower>=94)&&appStart) ; degree++){
            int changedValueFromController = map(analogRead(A0),180,880,93,145);
            if (changedValueFromController <=degree||hv>maxSpeed) break;
            htc=htc+degree+"　";
            SPX(degree);
            if (ost=0) ost=1;
            if (degree==94) delay(50); 
            else delay (MBR*ost);
            ASPXpower=degree;
            if (!brake) {
              lcd.setCursor(0,0);
              if ((degree-94)<0) RASPXpowerp=0;
              else RASPXpowerp=(degree-94)*100/51;
              lcd.print(RASPXpowerp);
              lcd.print("%       ");
              serialEvent();
              t++;
              if (t>2){
                String RASPXpowerpS = String (RASPXpowerp);
                Serial1.write('M');
                for(int i=0; i<RASPXpowerpS.length();i++)
                   Serial1.write(RASPXpowerpS[i]);
                Serial1.write('|');
                t=0;
              }
            }
          }
          Serial1.write('M');
          String RASPXpowerpS = String (RASPXpowerp);
          for(int i=0; i<RASPXpowerpS.length();i++)
             Serial1.write(RASPXpowerpS[i]);
          Serial1.write('|');
          t=0;
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
            lcd.setCursor(0,0);
            if ((ASPXpower-94)<0) RASPXpowerp=0;
            else RASPXpowerp=(ASPXpower-94)*100/51;
            lcd.print(RASPXpowerp);
            lcd.print("%       ");
            serialEvent();
            t++;
            if (t>2){
              String RASPXpowerpS = String (RASPXpowerp);
              Serial1.write('M');
              for(int i=0; i<RASPXpowerpS.length();i++)
                 Serial1.write(RASPXpowerpS[i]);
              Serial1.write('|');
              t=0;
            }
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
            htc=htc+ASPXpower+ost+"'";
            delay(100);
            if (!brake) {
              lcd.setCursor(0,0);
              if ((ASPXpower-94)<0) RASPXpowerp=0;
              else RASPXpowerp=(ASPXpower-94)*100/51;
              lcd.print(RASPXpowerp);
              lcd.print("%       ");
              serialEvent();
              t++;
              if (t>2){
                String RASPXpowerpS = String (RASPXpowerp);
                Serial1.write('M');
                for(int i=0; i<RASPXpowerpS.length();i++)
                   Serial1.write(RASPXpowerpS[i]);
                Serial1.write('|');
                t=0;
              }
            }
            Serial1.write('M');
            String RASPXpowerpS = String (RASPXpowerp);
            for(int i=0; i<RASPXpowerpS.length();i++)
               Serial1.write(RASPXpowerpS[i]);
            Serial1.write('|');
            t=0;
          }
        }
      }


   //Tell the condition
      if(SPXpower!=LSPXpower||ASPXpower!=LASPXpower){
        if (!err){
          Serial.print('X');
          Serial.print((SPXpower-94)*100/51);
          Serial.print(" ");
          Serial.print('M');
          Serial.print((ASPXpower-94)*100/51);
          Serial.print(" ");
          Serial.print('H');
          Serial.print("(");
          Serial.print(SPXpower);
          Serial.print(","); 
          Serial.print(LSPXpower);
          Serial.print(",");
          Serial.print(ASPXpower);
          Serial.print(",");
          Serial.print(LASPXpower);
          Serial.print(",");
          Serial.print(nowSpeed);
          Serial.print(",");
          Serial.print(maxSpeed);
          Serial.print(",");
          Serial.print(brake);
          Serial.print(")");
          Serial.print("\t");
          String SDSPX = "("+String(SPXpower)+","+String(LSPXpower)+","+String(ASPXpower)+","+String(LASPXpower)+","+String(nowSpeed)+","+String(maxSpeed)+","+String(brake)+")\t";
          if (!appStart){
            Serial.print("Bike LOCK");
            SDSPX+="Bike LOCK ";
          }
          else if ((ASPXpower==92||ASPXpower==93||ASPXpower==94)&&(LASPXpower==92||LASPXpower==93||LASPXpower==94)){
            Serial.print("BREAK STOPPED ");
            SDSPX+="BREAK STOPPED ";
          }
          else if ((ASPXpower==92||ASPXpower==93||ASPXpower==94)&&(LASPXpower!=92||LASPXpower!=93&&LASPXpower!=94)){
            Serial.print("BREAK STOPPING ");
            SDSPX+="BREAK STOPPING ";
          }
          else if (ASPXpower>=95&&ASPXpower<=141){
            Serial.print("FORWARD     ");
            SDSPX+="FORWARD     ";
          }
          else if (ASPXpower>=142&&ASPXpower<=179){
            Serial.print("MAX FORWARD ");
            SDSPX+="MAX FORWARD ";
          }
          SDSPX+=htc;
          Serial.println(htc);
          if (appStart) SDWrite(SDSPX);
        }
        
        lcd.setCursor(0,0);
        if (!err&&appStart){
          if (brake){
            lcd.print("Brk Active");
          }
          else if ( SPXpower<=94){
           lcd.print(0);
           lcd.print("%       ");
           RASPXpowerp=0;
          }
        }
      }

   //Make value of LASPXpower & LSPXpower
      LASPXpower=ASPXpower;
      LSPXpower = SPXpower;
}

void SPX(int power){
  SPX1.write(power);
  SPX2.write(power);  
}
