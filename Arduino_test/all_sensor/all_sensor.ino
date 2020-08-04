#include <SharpIR.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
#include <stdlib.h>

// ultra sensor
//#define MAX_DISTANCE 300
//NewPing sonar_L1(6, 7, MAX_DISTANCE);
//NewPing sonar_L2(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//NewPing sonar_R1(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//NewPing sonar_R2(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//const float V = 1/((331.5 + 0.607*31)/10000) ; 


// TOF sensor
SoftwareSerial TOF(2, 3);


//TF_Luna
SoftwareSerial TF_Luna(4, 5);
int uart[9];
const int HEADER = 0x59;
int check;

//struct
struct S {
  String mark;
  float dist;
};
struct S front_shortest_distance = {"None",0};



void setup() {
   Serial.begin(9600);
   TOF.begin(9600);
   TOF.setTimeout(100);
   TF_Luna.begin(115200);
}

void loop() {

//  int sonar_distanceL1=0, sonar_distanceL2=0, sonar_distanceR1=0, sonar_distanceR2=0;
  float tof_distance = 0;
  int luna_distance = 0;
  
  // get average value
  int times = 1;
  int tof_count = 0;
  int luna_count = 0;
  for(int i=0;i<times;i++) {

//    sonar_distanceL1 += sonar_L1.ping()/V/2;
//    sonar_distanceL2 += sonar_L2.ping()/V/2; 
//    sonar_distanceR1 += sonar_R1.ping()/V/2; 
//    sonar_distanceR2 += sonar_R2.ping()/V/2;

    
    if(TOF.available())
    {
      tof_count++;
      tof_distance = TOF.parseFloat();
      Serial.print("\t tof_distance: ");
      Serial.print(tof_distance);
    }

//    if (TF_Luna.available()) {
//      luna_count++;
//      if (TF_Luna.read() == HEADER) { 
//         uart[0] = HEADER;
//         if (TF_Luna.read() == HEADER) { 
//            uart[1] = HEADER;
//            for (i = 2; i < 9; i++) { 
//              uart[i] = TF_Luna.read();
//            }
//            check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
//            if (uart[8] == (check & 0xff)) { 
//              luna_distance = uart[2] + uart[3] * 256; 
//            
//          }
//        }
//      }
//    }
  }

  // average distance
//  sonar_distanceL1 /= times;
//  sonar_distanceL2 /= times;
//  sonar_distanceR1 /= times;
//  sonar_distanceR2 /= times;

  tof_distance /= tof_count;
  luna_distance /= luna_count;

//  if(sonar_distanceL1 < front_shortest_distance){
//    front_shortest_distance.name = "sonarL1";
//  }
//  if(sonar_distanceR1 < front_shortest_distance){
//    front_shortest_distance.name = "sonarR1";
//  }
//  if(tof_distance < front_shortest_distance){
//    front_shortest_distance.name = "sonarL1";
//  }
//  if(sonar_distanceL1 < front_shortest_distance){
//    front_shortest_distance.name = "sonarL1";
//  }




//  Serial.print("\t sonar_distanceL1: ");
//  Serial.print(sonar_distanceL1);

//  Serial.print("\t tof_distance: ");
//  Serial.print(tof_distance);

//  Serial.print("\t luna_distance: ");
//  Serial.println(luna_distance);

  

  

}
