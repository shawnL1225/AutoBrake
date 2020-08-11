/*
  HC-SR04 + LP40 + TF-Luna + SoftwareSerial
*/
#include <SoftwareSerial.h>
//2 TOF Sensor & SerialPost to Calculator Declare
SoftwareSerial Serial1(8, 13);//TF-Luna
SoftwareSerial Serial2(6, 7); //LP40
SoftwareSerial Serial3(A6, A7);//SendData

// defines pins numbers
const int trigLU = 9;
const int echoLU = 10;
const int trigLD = 11;
const int echoLD = 12;
const int trigRU = 5;
const int echoRU = 4;
const int trigRD = 3;
const int echoRD = 2;

// HC-SR04 Variables
int distanceLU;
int distanceLD;
int distanceRU;
int distanceRD;

//TF-Luna Variables
int TFLuna_Dist; //actual distance measurements of LiDAR
int strength; //signal strength of LiDAR
float temprature;
int check; //save check value
int i;
int uart[9]; //save data measured by LiDAR
const int HEADER = 0x59; //frame header of data package


//LP40 Variable
float LP40_Dist = 0;


int shortest_dist = 0;
int tof_dist = 0;

void setup() {
  pinMode(trigLU, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoLU, INPUT); // Sets the echoPin as an Input

  pinMode(trigLD, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoLD, INPUT); // Sets the echoPin as an Input

  pinMode(trigRU, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoRU, INPUT); // Sets the echoPin as an Input

  pinMode(trigRD, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoRD, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
  Serial1.begin(115200); //TF-Luna SerialPort
  Serial2.begin(115200); //LP40 SerialPort
  delay(20);
}
void loop() {
  shortest_dist = 4000;
  tof_dist = 4000;
  
  Serial1.listen(); //set bit rate of serial port connecting LiDAR with Arduino

  delay(30);
  
  if (Serial1.isListening()) {
    if (Serial1.available()) { //check if serial port has data input
      if (Serial1.read() == HEADER) { //assess data package frame header 0x59
        uart[0] = HEADER;
        if (Serial1.read() == HEADER) { //assess data package frame header 0x59
          uart[1] = HEADER;
          for (i = 2; i < 9; i++) { //save data in array
            uart[i] = Serial1.read();
          }
//          check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
//          if (uart[8] == (check & 0xff)) { //verify the received data as per protocol
            TFLuna_Dist = (uart[2] + uart[3] * 256)-3; //calculate distance value
            strength = uart[4] + uart[5] * 256; //calculate signal strength value
            //          temprature = (uart[6] + uart[7] * 256)/8 - 256; //calculate chip temprature
            //Serial.print('\t');
            //Serial.print("strength = ");
            //Serial.println(strength); //output signal strength value
//            Serial.print("TFLuna: ");
//            Serial.print(TFLuna_Dist);

            if(TFLuna_Dist>0 && TFLuna_Dist<180 ){
               tof_dist = TFLuna_Dist;
               
               if( TFLuna_Dist<shortest_dist){
                  shortest_dist = TFLuna_Dist;
                }
            }
            
              
//          }
        }
      }
    }
  }


  Serial2.listen(); //set bit rate of serial port connecting LiDAR with Arduino
  delay(30);
  
  if (Serial2.isListening()) {
    if (Serial2.available() > 0) {
      LP40_Dist = Serial2.parseFloat();
      LP40_Dist*=100;
//      Serial.print("\t LP40: ");
//      Serial.print(LP40_Dist);

      if(LP40_Dist!=6000 && LP40_Dist>180 && TFLuna_Dist>180) {
          tof_dist = LP40_Dist;
          
          if(LP40_Dist<shortest_dist){
             shortest_dist = LP40_Dist;
          }
      }
    }
  }

  distanceLU = getDistance(trigLU, echoLU);
  distanceLD = getDistance(trigLD, echoLD);
  distanceRU = getDistance(trigRU, echoRU);
  distanceRD = getDistance(trigRD, echoRD);

  // Prints the distance on the Serial Monitor


    Serial.print("\ts: ");
    Serial.print(shortest_dist);
    Serial.print("\tt: ");
    Serial.println(tof_dist);

//      Serial.print("\tLD: ");
//  Serial.print(distanceLD);
//  Serial.print("\tLU: ");
//  Serial.print(distanceLU);
//  
//  Serial.print("\tRU: ");
//  Serial.print(distanceRU);
//  Serial.print("\tRD: ");
//  Serial.println(distanceRD);
}



int getDistance(int trigPin, int echoPin) {
  long duration;
  int distance;
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH, 23530);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  if(distance!=0 && tof_dist-distance > 20 && distance<shortest_dist){
    shortest_dist = distance;
  }

  return distance;
}
