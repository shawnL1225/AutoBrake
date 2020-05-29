#include <SharpIR.h>
#define IRPin1 A0
#define IRPin2 A1
#define model 100500
int distance_cm_1;
int distance_cm_2;
int dou_distance_cm;
int ave_distance_cm;
SharpIR mySensor1 = SharpIR(IRPin1, model);
SharpIR mySensor2 = SharpIR(IRPin2, model);
void setup() {

  Serial.begin(9600);
}
void loop() {  
  for(char i=0;i<10;i++) {                       //for 迴圈，迴圈10次
    distance_cm_1 = mySensor1.distance();
    distance_cm_2 = mySensor2.distance();
    distance_cm_1 = distance_cm_1*1.12;
    distance_cm_2 = distance_cm_2*1.12;
    dou_distance_cm = distance_cm_1+distance_cm_2;
    dou_distance_cm = dou_distance_cm /2;
    
    ave_distance_cm = ave_distance_cm + dou_distance_cm;                
   }
   ave_distance_cm = ave_distance_cm / 10; //將加了10次的值除10得平均


  Serial.print("  Sensor1: ");
  Serial.print(distance_cm_1);
  Serial.print(" cm");
  Serial.print("      Sensor2: ");
  Serial.print(distance_cm_2);
  Serial.print("cm");
  Serial.print("          Double_Sensor: ");
  Serial.print(dou_distance_cm);
  Serial.print("cm");
  delay(200);
  Serial.print("              Ave_Mean distance: ");
  Serial.print(ave_distance_cm);
  Serial.println("cm");                     
  delay(500);                                   //延遲 1秒
   ave_distance_cm = 0;                          //將ave_distance_cm清為0
  }
