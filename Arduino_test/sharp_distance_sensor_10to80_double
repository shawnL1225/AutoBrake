#include <SharpIR.h>
#define IRPin1 A0
#define IRPin2 A1
#define model 1080
int x;
int y;
int V, Distance1 ;
int Z, Distance2 ;
int dou_distance_cm;
int ave_distance_cm;
SharpIR mySensor1 = SharpIR(IRPin1, model);
SharpIR mySensor2 = SharpIR(IRPin2, model);
void setup() {
Serial.begin(9600);
}

void loop() {
x = analogRead(A0);
y = analogRead(A1);
V = x*5.000000/1023.000000 ;
Z = y*5.000000/1023.000000 ;
Distance1 = 29.988*pow(V , -1.173); //GP2Y0A21YK (1080)
Distance2 = 29.988*pow(Z , -1.173); //GP2Y0A21YK (1080)

  for(char i=0;i<10;i++) {                       //for 迴圈，迴圈10次
    Distance1 = mySensor1.distance();
    Distance2 = mySensor2.distance();
    Distance1 = Distance1 *1.3;
    Distance2 = Distance2 *1.4;
    dou_distance_cm = Distance1 + Distance2;
    dou_distance_cm = dou_distance_cm /2;
    
    ave_distance_cm = ave_distance_cm + dou_distance_cm;                
   }
   ave_distance_cm = ave_distance_cm / 10; //將加了10次的值除10得平均

  Serial.print("  Sensor1: ");
  Serial.print(Distance1);
  Serial.print(" cm");
  Serial.print("      Sensor2: ");
  Serial.print(Distance2);
  Serial.print("cm");
  Serial.print("          Double_Sensor: ");
  Serial.print(dou_distance_cm);
  Serial.print("cm");
  delay(100);
  Serial.print("              Ave_Mean distance: ");
  Serial.print(ave_distance_cm);
  Serial.println("cm");                     
  delay(900);                                   //延遲 1秒
   ave_distance_cm = 0;                          //將ave_distance_cm清為0
  }
