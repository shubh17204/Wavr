#include <EEPROM.h>
void setup() {
  // put your setup code here, to run once:

  int EEPROM_MEMORY_SIZE = 32;  
  EEPROM.begin(EEPROM_MEMORY_SIZE);
  
  for (int i = 0; i<EEPROM_MEMORY_SIZE; i++){
    EEPROM.write(i,0);
  }

  EEPROM.commit();
  EEPROM.end();
}

void loop() {
  // put your main code here, to run repeatedly:

}
