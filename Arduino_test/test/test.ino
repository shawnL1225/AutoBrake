#include <SharpIR.h>
#include <NewPing.h>
#include <stdlib.h>
#include <SoftwareSerial.h>

// ultra sensor
#define MAX_DISTANCE 300
//NewPing sonar_L1(6, 7, MAX_DISTANCE);
//NewPing sonar_L2(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//NewPing sonar_R1(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//NewPing sonar_R2(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
const float V = 1/((331.5 + 0.607*31)/10000) ; 


SoftwareSerial Serial1(2, 3);




// TOF sensor
float tof_distance = 0;


void setup() {
   Serial.begin(9600);
   Serial1.begin(9600);
}

void loop() {
  
  int ir_distanceT=0, ir_distanceB=0;
  int sonar_distanceL1=0, sonar_distanceL2=0, sonar_distanceR1=0, sonar_distanceR2=0;
  
  
  // get average value
  int times = 10;
  int tof_count = 0;
  for(int i=0;i<times;i++) {

//
//    sonar_distanceL1 += sonar_L1.ping()/V/2;
//    sonar_distanceL2 += sonar_L2.ping()/V/2; 
//    sonar_distanceR1 += sonar_R1.ping()/V/2; 
//    sonar_distanceR2 += sonar_R2.ping()/V/2;

    
    if(Serial1.available()>0)
    {
      tof_count++;
      tof_distance += Serial1.parseFloat();
    } 
  }

//
//  sonar_distanceL1 /= times;
//  sonar_distanceL2 /= times;
//  sonar_distanceR1 /= times;
//  sonar_distanceR2 /= times;

  tof_distance /= tof_count;




//  Serial.print("\t sonar_distanceL1: ");
//  Serial.print(sonar_distanceL1);

  Serial.print("\t tof_distance: ");
  Serial.println(tof_distance);

}
