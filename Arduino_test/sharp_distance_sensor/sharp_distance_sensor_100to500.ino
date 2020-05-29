/*SHARP GP2Y0A710K0F IR sensor with Arduino and SharpIR library example code. More info: https://www.makerguides.com */
// Include the library:
#include <SharpIR.h>
// Define model and input pin:
#define IRPin A0
#define model 100500
// Create variable to store the distance:
int distance_cm;
/* Model :
  GP2Y0A02YK0F --> 20150
  GP2Y0A21YK0F --> 1080
  GP2Y0A710K0F --> 100500
  GP2YA41SK0F --> 430
*/
// Create a new instance of the SharpIR class:
SharpIR mySensor = SharpIR(IRPin, model);
void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
}
void loop() {
  // Get a distance measurement and store it as distance_cm:
  distance_cm = mySensor.distance();
  // Print the measured distance to the serial monitor:
  Serial.print("Mean distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  delay(100);
  }
