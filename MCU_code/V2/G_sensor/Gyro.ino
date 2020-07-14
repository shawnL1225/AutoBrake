void gyro(){
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  dx= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  dy= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  dz= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  dx = dx+fixdx;
  dy = dy+fixdy;
  dz = dz+fixdz;
  
  if (dx<-180) dx+=360;
  if (dy<-180) dy+=360;
  if (dz<-180) dz+=360;
  if (dx>180) dx-=360;
  if (dy>180) dy-=360;
  if (dz>180) dz-=360;
  
}
