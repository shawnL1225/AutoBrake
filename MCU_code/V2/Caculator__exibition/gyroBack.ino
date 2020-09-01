void gyroBack(){
  Wire.beginTransmission(MPU6050BackAddr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050BackAddr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  double Bdx= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  double Bdy= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  double Bdz= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  Bdx = Bdx+fixBdx;
  Bdy = Bdy+fixBdy;
  Bdz = Bdz+fixBdz;
  
  if (Bdx<-180) Bdx+=360;
  if (Bdy<-180) Bdy+=360;
  if (Bdz<-180) Bdz+=360;
  if (Bdx>180) Bdx-=360;
  if (Bdy>180) Bdy-=360;
  if (Bdz>180) Bdz-=360;

  riseAngle = Bdy;
  flipAngle = Bdz;
  backRotateAngle = Bdx;
  
//  Serial.print("riseAngle : ");
//  Serial.print(riseAngle);
//  Serial.print("flipAngle : ");
//  Serial.println(riseAngle);

//  Serial.print("BrotateAngle : ");
//  Serial.println(backRotateAngle);
//  Serial.print(" z : ");
//  Serial.println(dz);
}
