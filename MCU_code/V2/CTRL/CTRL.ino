#include <SoftwareSerial.h>

SoftwareSerial Serial4(10,11);//(RX,TX)

int CTRLP = 0, LCTRLP=0 ;
int maxSpeed = 25, nowSpeed = 0;

unsigned long lbsms=0;

double hv=0, lhv=0;                 //hv -> received velocity ; lhv-> last received velocity (unit:km/hr)
