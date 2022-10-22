
void set_pushbutton_data() {
  if (digitalRead(push_button)) {
    gloveDataObject.push_button_state = true;
  } else {
    gloveDataObject.push_button_state = false;
  }
}

String pushButtonStringify(){
  if (gloveDataObject.push_button_state) {
    return String("BD-");
  } else {
    return String("BU-");
  }

}

void flashNVS() {
 preferences.begin("calib-data", false);
 preferences.clear();
 preferences.end();
}
