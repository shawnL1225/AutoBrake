<<<<<<< HEAD
void gyroFront() {
  Wire.beginTransmission(MPU6050_front_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU6050_front_addr, 7 * 2, true); // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  // print out data
  Serial.print("Front gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | Front gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | Front gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();
=======
void gyroFront(){
  Wire.beginTransmission(MPU6050FrontAddr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050FrontAddr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  double dx= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  double dy= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  double dz= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  dx = dx+fixFdx;
  dy = dy+fixFdy;
  dz = dz+fixFdz;
  
  if (dx<-180) dx+=360;
  if (dy<-180) dy+=360;
  if (dz<-180) dz+=360;
  if (dx>180) dx-=360;
  if (dy>180) dy-=360;
  if (dz>180) dz-=360;

  frontRotate = dx;
  
  Serial.print("frontRotate x: ");
  Serial.println(dx);
//  Serial.print(" y : ");
//  Serial.println(dy);
//  Serial.print(" z : ");
//  Serial.println(dz);
>>>>>>> 262c727481c08d506d4fb744d3ac987be608e22e
}
