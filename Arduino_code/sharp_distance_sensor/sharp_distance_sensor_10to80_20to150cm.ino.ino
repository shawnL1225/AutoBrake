#include <Wire.h>
int x;
float V, Distance ;

void setup() {
Serial.begin(9600);
}

void loop() {
x = analogRead(A0);
V = x*5.000000/1023.000000 ;
//Distance = 60.374*pow(V , -1.16); //GP2Y0A02YK0F (20150)
//Distance = 29.988*pow(V , -1.173); //GP2Y0A21YK (1080)
//Distance (cm)= 27.726X POW(Output_voltage, -1.2045)
//Distance = 12.08*pow(V , -1.058);  //GP2YA41SK0F (0430)
Distance = 299.88*pow(V , -1.375); //GP2Y0A21YK (137500)
//Distance (cm) = 1/((Output_voltage_mV – 1125)/137500)

Serial.print("Distance=");
Serial.print(Distance);
Serial.println("   cm ");

delay(100);
}
