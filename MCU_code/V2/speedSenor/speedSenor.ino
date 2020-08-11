#include <SoftwareSerial.h>
SoftwareSerial Serial4(10,11); //(RX,TX)

bool magnet1, magnet2, lmagnet1=1, lmagnet2=1;
unsigned long rms, ms1, lms1, ms2, lms2;
int ts1, ts2;
int errt = 9000, pri =0; 
double sv1, sv2, hv1=0, hv2=0, lhv1, lhv2, fhv, lfhv=0, printed=0;
