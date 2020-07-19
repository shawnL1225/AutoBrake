#include <SharpIR.h>
#include <stdlib.h>
#define IRPin1 A0
#define IRPin2 A1
#define model 100500
int distanceR, distanceL;
int ave_distanceR, ave_distanceL;

int duoAve_distance;
int diff_distance;
SharpIR mySensorR = SharpIR(IRPin1, model);
SharpIR mySensorL = SharpIR(IRPin2, model);


void setup() {

  Serial.begin(9600);
}

void loop() {  

  ave_distanceR = 0;
  ave_distanceL = 0;
  
  //for 迴圈，迴圈10次
  for(char i=0;i<10;i++) {
    distanceR = mySensorR.distance();
    distanceL = mySensorL.distance();


    ave_distanceR += distanceR;
    ave_distanceL += distanceL;
   }
   
  ave_distanceR /= 10;
  ave_distanceL /= 10;
 
  diff_distance = abs(ave_distanceR-ave_distanceL);
  duoAve_distance = (ave_distanceR+ave_distanceL)/2;

  Serial.print("ave_distanceR:  ");
  Serial.print(ave_distanceR);
  Serial.print(" cm");

  Serial.print("\t ave_distanceL:  ");
  Serial.print(ave_distanceL);
  Serial.print(" cm");

  Serial.print("\t duoAve_distance:  ");
  Serial.print(duoAve_distance);
  Serial.print(" cm");

  Serial.print("\t diff_distance:  ");
  Serial.print(diff_distance);
  Serial.println(" cm");


               
  delay(500);
  

  }
