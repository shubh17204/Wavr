
void calibrate_flex_sensor_range(const char* locationIdentifier) {

  int max_calibrations_iter = 256;
  bool tempStoreMainToken = mainTokenStatus;
  mainTokenStatus = false;
    
preferences.begin("calib-data", false);
  int hasAlreadyCalibrated = preferences.getUInt("hasCalib", 0);
  
  if (hasAlreadyCalibrated && locationIdentifier == "self") {

    R_THUMB_FLAT_RES = preferences.getUInt("thumbMin", 75);
    R_INDEX_FLAT_RES = preferences.getUInt("indexMin", 75;
    R_MIDDLE_FLAT_RES = preferences.getUInt("middleMin", 75);
    R_RING_FLAT_RES = preferences.getUInt("ringMin", 75);
    R_FIFTH_FLAT_RES = preferences.getUInt("fifthMin", 75);

    R_THUMB_BENT_RES = preferences.getUInt("thumbMax", 2700);
    R_INDEX_BENT_RES = preferences.getUInt("indexMax", 2700);
    R_MIDDLE_BENT_RES = preferences.getUInt("middleMax", 2700);
    R_INDEX_BENT_RES = preferences.getUInt("ringMax", 2700);
    R_INDEX_BENT_RES = preferences.getUInt("fifthMax", 2700);

    preferences.end();
    return;
  }
  
  service.fade_out_red(0,15);
  
  delay(3000);

  haptic_chime_start();
  delay(2000);

  //For flat calibration
  int thumb_values = 0;
  int index_values = 0;
  int middle_values = 0;
  int ring_values = 0;
  int fifth_values = 0;

  for(int iteration = 0; iteration < max_calibrations_iter; iteration++) { 
    thumb_values += analogRead(right_flex_thumb);
    index_values += analogRead(right_flex_index);
    middle_values += analogRead(right_flex_middle);
    ring_values += analogRead(right_flex_ring);
    fifth_values += analogRead(right_flex_fifth);

    if (iteration % 4 == 0) {
      service.set_yellow_LED(iteration/4);
    }
    delay(30);
  }
  R_THUMB_FLAT_RES = thumb_values/max_calibrations_iter;
  R_INDEX_FLAT_RES = index_values/max_calibrations_iter;
  R_MIDDLE_FLAT_RES = middle_values/max_calibrations_iter;
  R_RING_FLAT_RES = ring_values/max_calibrations_iter;
  R_FIFTH_FLAT_RES = fifth_values/max_calibrations_iter;  

  preferences.putUInt("thumbMin", R_THUMB_FLAT_RES);
  preferences.putUInt("indexMin", R_INDEX_FLAT_RES);
  preferences.putUInt("middleMin", R_MIDDLE_FLAT_RES);
  preferences.putUInt("ringMin", R_RING_FLAT_RES);
  preferences.putUInt("fifthMin", R_FIFTH_FLAT_RES);

  haptic_chime_stop();
  
  service.stop_LED();

  delay(3000);

  haptic_chime_start();
  delay(2000);

  //For bent calibration
  thumb_values = 0;
  index_values = 0;
  middle_values = 0;
  ring_values = 0;
  fifth_values = 0;

  for (int iteration = 0; iteration < max_calibrations_iter; iteration++) {
    
    thumb_values += analogRead(right_flex_thumb);
    index_values += analogRead(right_flex_index);
    middle_values += analogRead(right_flex_middle);
    ring_values += analogRead(right_flex_ring);
    fifth_values += analogRead(right_flex_fifth);

    if (iteration % 4 == 0) {
      service.set_yellow_LED(iteration/4);
    }
    delay(30);
  }
  R_THUMB_BENT_RES = bthumb_values/max_calibrations_iter;
  R_INDEX_BENT_RES = bindex_values/max_calibrations_iter;
  R_MIDDLE_BENT_RES = bmiddle_values/max_calibrations_iter;
  R_RING_BENT_RES = bring_values/max_calibrations_iter;
  R_FIFTH_BENT_RES = bfifth_values/max_calibrations_iter;  

  preferences.putUInt("thumbMax", R_THUMB_BENT_RES);
  preferences.putUInt("indexMax", R_INDEX_BENT_RES);
  preferences.putUInt("middleMax", R_MIDDLE_BENT_RES);
  preferences.putUInt("ringMax", R_RING_BENT_RES);
  preferences.putUInt("fifthMax", R_FIFTH_BENT_RES);
  hasAlreadyCalibrated = 1;
  preferences.putUInt("hasCalib", hasAlreadyCalibrated);
  //  Serial.println("Simple:");
  //  Serial.println(R_THUMB_FLAT_RES);
  //  Serial.println(R_THUMB_BENT_RES); 
  preferences.end();

  mainTokenStatus = tempStoreMainToken;

  delay(1500);
  haptic_chime_success();
  service.set_purple_LED(64);


  //ESP.restart();
}
