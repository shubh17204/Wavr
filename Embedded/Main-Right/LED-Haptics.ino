
void boot_LED_haptic_routine() {
  for (int fadeValue = 0; fadeValue < 128; fadeValue += 5) {
    service.set_haptor(fadeValue+32);
    service.set_red_LED(fadeValue);
    delay(60);
  }
  service.set_haptor(0);
  for (int fadeValue = 127; fadeValue > 0; fadeValue -= 5) {
    service.set_red_LED(fadeValue);
    delay(30);
  }
  for (int fadeValue = 0; fadeValue < 128; fadeValue += 5) {
    service.set_haptor(fadeValue+32);
    service.set_red_LED(fadeValue);
    delay(60);
  }
  service.set_haptor(0);
  for (int fadeValue = 127; fadeValue > 0; fadeValue -= 5) {
    service.set_red_LED(fadeValue);
    delay(30);
  }

  for (int fadeValue = 0; fadeValue < 255; fadeValue += 5) {
//    service.set_haptor(fadeValue);
    service.set_red_LED(fadeValue);
    delay(30);
  }
  
  delay(100);
  service.set_haptor(0);
  delay(500);
}

void haptic_chime_success() {
  service.set_haptor(205);
  delay(200);
  
  service.set_haptor(0);
  delay(150);

  service.set_haptor(205);
  delay(200);
  
  service.set_haptor(0);
}

void haptic_chime_error() {
  for (int fadeValue = 125; fadeValue < 200; fadeValue += 5) {
    service.set_haptor(fadeValue);
    delay(45);
  }  
  service.set_haptor(0);
}

void haptic_chime_start() {
  service.set_haptor(0);

  service.set_haptor(75);
  delay(250);

  service.set_haptor(200);
  delay(200);

  service.set_haptor(0);

}

void haptic_chime_stop() {
  service.set_haptor(0);

  service.set_haptor(200);
  delay(200);

  service.set_haptor(75);
  delay(250);

  service.set_haptor(0);
}
