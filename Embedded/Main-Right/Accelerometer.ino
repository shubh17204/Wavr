void setup_accelerometer(){

  Wire.begin();
  mpu.begin();
  mpu.calcOffsets(true,true);

}

void set_accelerometer_data(){

  gloveDataObject.right_pitch = mpu.getAngleX(); //pitch
  gloveDataObject.right_roll = mpu.getAngleY(); //roll
  gloveDataObject.right_yaw = mpu.getAngleZ(); //yaw

  gloveDataObject.right_rot_X = mpu.getGyroX();
  gloveDataObject.right_rot_Y = mpu.getGyroY();
  gloveDataObject.right_rot_Z = mpu.getGyroZ();
}
