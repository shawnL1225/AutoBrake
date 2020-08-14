void gyroBack(){
  Wire.beginTransmission(MPU6050_back_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_back_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  double dx= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  double dy= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  double dz= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  dx = dx+fixdx;
  dy = dy+fixdy;
  dz = dz+fixdz;
  
  if (dx<-180) dx+=360;
  if (dy<-180) dy+=360;
  if (dz<-180) dz+=360;
  if (dx>180) dx-=360;
  if (dy>180) dy-=360;
  if (dz>180) dz-=360;

  riseAngle = dx;
  rotateAngle = dy;
  
  Serial.print("G x: ");
  Serial.print(dx);
  Serial.print(" y : ");
  Serial.println(dy);
//  Serial.print(" z : ");
//  Serial.println(dz);
}
