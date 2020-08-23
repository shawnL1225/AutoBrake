////void gyroBack(){
////  Wire.beginTransmission(MPU6050BackAddr);
////  Wire.write(0x3B);
////  Wire.endTransmission(false);
////  Wire.requestFrom(MPU6050BackAddr,14,true);
////  AcX=Wire.read()<<8|Wire.read();
////  AcY=Wire.read()<<8|Wire.read();
////  AcZ=Wire.read()<<8|Wire.read();
////  
////  int xAng = map(AcX,minVal,maxVal,-90,90);
////  int yAng = map(AcY,minVal,maxVal,-90,90);
////  int zAng = map(AcZ,minVal,maxVal,-90,90);
////
////  double dx= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
////  double dy= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
////  double dz= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
////
////  dx = dx+fixBdx;
////  dy = dy+fixBdy;
////  dz = dz+fixBdz;
////  
////  if (dx<-180) dx+=360;
////  if (dy<-180) dy+=360;
////  if (dz<-180) dz+=360;
////  if (dx>180) dx-=360;
////  if (dy>180) dy-=360;
////  if (dz>180) dz-=360;
////
////  riseAngle = dy;
////  flipAngle = dz;
////  backRotateAngle = dx;
////  
//////  Serial.print("riseAngle : ");
//////  Serial.print(riseAngle);
//////  Serial.print("flipAngle : ");
//////  Serial.println(riseAngle);
////
//////  Serial.print("BrotateAngle : ");
//////  Serial.println(backRotateAngle);
//////  Serial.print(" z : ");
//////  Serial.println(dz);
////}
//void gyroBack(){
//  Wire.beginTransmission(MPU6050BackAddr);
//  Wire.write(0x3B);
//  Wire.endTransmission(false);
//  Wire.requestFrom(MPU6050BackAddr,14,true);
//  AcX=Wire.read()<<8|Wire.read();
//  AcY=Wire.read()<<8|Wire.read();
//  AcZ=Wire.read()<<8|Wire.read();
//  
//  int xAng = map(AcX,minVal,maxVal,-90,90);
//  int yAng = map(AcY,minVal,maxVal,-90,90);
//  int zAng = map(AcZ,minVal,maxVal,-90,90);
//
//  double dx= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
//  double dy= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
//  double dz= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
//
//  dx = dx+fixBdx;
//  dy = dy+fixBdy;
//  dz = dz+fixBdz;
//  
//  if (dx<-180) dx+=360;
//  if (dy<-180) dy+=360;
//  if (dz<-180) dz+=360;
//  if (dx>180) dx-=360;
//  if (dy>180) dy-=360;
//  if (dz>180) dz-=360;
//
//  riseAngle = dx;
//  flipAngle = dy;
//  BrotateAngle = dz;
//  
//  Serial.print("riseAngle : ");
//  Serial.print(dx);
//  Serial.print("flipAngle : ");
//  Serial.print(dy);
//  Serial.print("BrotateAngle : ");
//  Serial.println(dz);
////  Serial.print(" z : ");
////  Serial.println(dz);
//}
