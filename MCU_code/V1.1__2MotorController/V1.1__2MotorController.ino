#include <Wire.h>  
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
  
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // set lcd I2C address
Servo SPX1, SPX2;     //The motor controller get value in Servo type
File  file;           //SD card 

int maxSpeed=100;     //Max speed for bike
int ASPXpower=92;     //Actual final power for SPX
int LASPXpower=92;    //Last value of incame SPXpower
int LSPXpower=92;     //Last actual final power for SPX
int RASPXpowerp=0;    //Real time ASPXpower percentage
int ost=0, MBR=30 ;   //over speed time
int VGALED=13;        //VGA connection light
int fixhr=0,fixmi=0,fixsec=0,fixmsec=0;  //Add time to arduino millisecond

unsigned long S2lms=0, S2ms=0, lbsms=0;      // To caculate the time lag between one another

double hv=0, lhv=0;                 //hv -> received velocity ; lhv-> last received velocity (unit:km/hr)

bool lerr=0, err=0;   //error occur
bool brake;           //is brake active
bool appStart=0;      //does app allow controller to start

String fileName, lBV/*last battery voltage*/, lsS;/*last speed String*/

//-----------------------------Main Code-------------------------------------------
  void loop() {
    
  // get value from controller [controller value]
    int valueFromController=analogRead(A0);                   //value could be from 0~1023, normal value should be within 180~880
    int SPXpower = map(valueFromController,182,880,93,145);   //turn analogvalue to servo degree
    
  // get value of brake   [brake]
    int brakeV = analogRead(A10);
    if (brakeV<300) brake =1;
    else if (brakeV>=300) brake=0;
    brake=0;
    
  // go to  motor loop
    motor(SPXpower, hv, brake);
    
  // go to serialEvent
      serialEvent();

  //Take botton be press on the controller
    if (!digitalRead(8)) {
      Serial1.print("W1|");
      delay(1500);
      Serial1.print("W0|");
    }
  //if error occur //to keep blinking on the screen//
    if (err){
      lcd.setCursor(0,0);
      lcd.print("Err Occ     ");
      delay(500);
      lcd.setCursor(0,0);
      lcd.print("Check Phone");
      delay(500);
    }
    
    if (((ASPXpower<95&&millis()-lbsms>3000)||lbsms==0)&&appStart){
        int r = random(20,23);
        Serial.print('T');
        Serial.print(r);
        Serial.println(' ');
        delay(10);
//        battery();
        Serial1.print("B90|");
        lbsms=millis();
        Serial1.print('T');
        Serial1.print(r);
        Serial1.print('|');
        
    }
    if (!digitalRead(39)){
      Serial1.print("Z1f|");
      Serial.println("Z|");
      Serial.println(analogRead(A2));
      digitalWrite(24,1);
      while (analogRead(2)>310){
        Serial.println(analogRead(A2));
        if (analogRead(2)<=310){
          digitalWrite(24,0);
          break; 
        }
      }
      if (analogRead(2)<=310){
          digitalWrite(24,0);
        }
      
      delay(5000);
      digitalWrite(22,1);
      while (analogRead(2)<785){
        Serial.println(analogRead(A2));
        if (analogRead(2)>=735){
          digitalWrite(22,0);
          break;
        }
      }
      if (analogRead(2)>=735){
          digitalWrite(22,0);
      }
      Serial1.print("Z0|");
    }
  }
