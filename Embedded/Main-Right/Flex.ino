int get_Bend_Angle(int fingerPin, int flatResistance, int bendResistance) {

  int ADCflex = analogRead(fingerPin);
  float angle = ( (ADCflex - flatResistance) * 100 ) / (bendResistance + 1);
//    if (fingerPin == right_flex_thumb) {
//      Serial.print("reading: ");
//      Serial.println(ADCflex);
//    Serial.println(angle);
//  
//  }
  if (angle < 0) {
    angle = 0;
  }
  if (angle > 99) {
    angle = 99;
  }
  return angle;
}

void set_flex_data() {
  
  gloveDataObject.right_thumb_angle = get_Bend_Angle(right_flex_thumb, R_THUMB_FLAT_RES, R_THUMB_BENT_RES);
  gloveDataObject.right_index_angle = get_Bend_Angle(right_flex_index, R_INDEX_FLAT_RES, R_INDEX_BENT_RES);
  gloveDataObject.right_middle_angle = get_Bend_Angle(right_flex_middle, R_MIDDLE_FLAT_RES, R_MIDDLE_BENT_RES);
  gloveDataObject.right_ring_angle = get_Bend_Angle(right_flex_ring, R_RING_FLAT_RES, R_RING_BENT_RES);
  gloveDataObject.right_fifth_angle = get_Bend_Angle(right_flex_fifth, R_FIFTH_FLAT_RES, R_FIFTH_BENT_RES);
}

String flexStringify(int fingerAngle) {
  if (fingerAngle >9) {
    return String(fingerAngle) + "-";
  } else {
    String str = "0";
    str += fingerAngle;
    return str + "-";
  }
}
