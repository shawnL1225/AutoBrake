#include <SoftwareSerial.h>

SoftwareSerial Serial4(10,11);//(RX,TX)

int maxSpeed=100;     //Max speed for bike
int ASPXpower=92;     //Actual final power for SPX
int LASPXpower=92;    //Last value of incame SPXpower
int LSPXpower=92;     //Last actual final power for SPX
int RASPXpowerp=0;    //Real time ASPXpower percentage
int ost=0, MBR=30 ;   //over speed time
int t;                //into loop time

unsigned long S2lms=0, S2ms=0, lbsms=0;      // To caculate the time lag between one another

double hv=0, lhv=0;                 //hv -> received velocity ; lhv-> last received velocity (unit:km/hr)

bool lerr=0, err=0;   //error occur
bool brake;           //is brake active
bool appStart=0;      //does app allow controller to start
