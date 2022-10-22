/* 
Wavr Augmentation Gloves
A Project by Jaskaran Singh

Sketch For: WAVR GLOVE - RIGHT | SCHEMATIC REV 0.1
*/

#include <Preferences.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);
Preferences preferences;

//DEFINE STATEMENTS

//Finger Flex Array Definitions
#define right_flex_thumb 36
#define right_flex_index 39
#define right_flex_middle 34
#define right_flex_ring 35
#define right_flex_fifth 32

//RGB LED Light Definitions
#define LED_red 25
#define LED_green 26
#define LED_blue 27

//Haptic Motor Definition
#define haptic_motor 33

//Accelerometer Module Definitions
#define accelerometer_SCL 22
#define accelerometer_SDA 21

//Push Button Definition
#define push_button 13

#define RX_PIN 3


//GLOBAL VARIABLES
int BAUD_RATE = 115200;
int HAPTIC_MOTOR_VALUE = 0;
int LED_RED_VALUE = 0;
int LED_GREEN_VALUE = 0;
int LED_BLUE_VALUE = 0;
bool PUSH_BUTTON_STATUS = 0;
bool mainTokenStatus = false;

//FLEX SENSOR RANGE VALUES
int R_THUMB_FLAT_RES = 0.0;
int R_THUMB_BENT_RES = 0.0;
int R_INDEX_FLAT_RES = 0.0;
int R_INDEX_BENT_RES = 0.0;
int R_MIDDLE_FLAT_RES = 0.0;
int R_MIDDLE_BENT_RES = 0.0;
int R_RING_FLAT_RES = 0.0;
int R_RING_BENT_RES = 0.0;
int R_FIFTH_FLAT_RES = 0.0;
int R_FIFTH_BENT_RES = 0.0;

//CUSTOM CLASSES

class RightGloveMainDataObject {
  
  //Push Button status
  public: bool push_button_state = 0;

  //Flex Sensor Array Values
  
  public: int right_thumb_angle = 99;
  public: int right_index_angle = 99;
  public: int right_middle_angle = 99;
  public: int right_ring_angle = 99;
  public: int right_fifth_angle = 99;

  //Acceleration Values
  public: int right_rot_X = 0;
  public: int right_rot_Y = 0;
  public: int right_rot_Z = 0;

  //Rotation Values  
  public: int right_pitch = 0;
  public: int right_roll = 0;
  public: int right_yaw = 0;
} gloveDataObject;

BLECharacteristic *pCharacteristic;

class Services{
//LED SERVICES
  public: void set_red_LED(int intensity) {
    LED_RED_VALUE = intensity;
    analogWrite(LED_red, LED_RED_VALUE);
  }
    public: void set_green_LED(int intensity) {
    LED_GREEN_VALUE = intensity;
    analogWrite(LED_green, LED_GREEN_VALUE);
  }
    public: void set_blue_LED(int intensity) {
    LED_BLUE_VALUE = intensity;
    analogWrite(LED_blue, LED_BLUE_VALUE);
  }
  public: void set_white_LED(int intensity) {
    set_red_LED(intensity);
    set_green_LED(intensity);
    set_blue_LED(intensity);
  }
  public: void stop_LED() {
    set_white_LED(0);
  }
    public: void set_yellow_LED(int intensity) {
    set_red_LED(intensity);
    set_green_LED(intensity);
    set_blue_LED(0);
  }
  public: void set_purple_LED(int intensity) {
    set_red_LED(intensity);
    set_green_LED(0);
    set_blue_LED(intensity);
  }
  public: void set_cyan_LED(int intensity) {
    set_red_LED(0);
    set_green_LED(intensity);
    set_blue_LED(intensity);
  }
  public: void fade_in_red(int to, int delayy) {
    for (int fadeValue = LED_RED_VALUE; fadeValue < to; fadeValue += 5) {
    set_red_LED(fadeValue);
    delay(delayy);
    }
  }
  public: void fade_out_red(int to, int delayy) {
    set_cyan_LED(0);
    for (int fadeValue = LED_RED_VALUE; fadeValue > to; fadeValue -= 5) {
    set_red_LED(fadeValue);
    delay(delayy);
    }
  }
  
  public: void set_haptor(int intensity){
    HAPTIC_MOTOR_VALUE = intensity;
    analogWrite(haptic_motor, HAPTIC_MOTOR_VALUE);
  }

  public: void ping() {
    pCharacteristic->setValue("Hello from Wavr");
    pCharacteristic->notify();
  } 

  public: void notifyError() {
  pCharacteristic->setValue("No Such Service Exists");
  pCharacteristic->notify();
  } 

} service ;
  void calibrate_flex_sensor_range(const char* locationIdentifier);
  void haptic_chime_start(); 
  void haptic_chime_success();
  void haptic_chime_error();
  void haptic_chime_stop();
  void flashNVS();
  void boot_LED_haptic_routine();

//BLE SETUP
  //UUID
  #define SERVICE_UUID        "0160667a-94f7-4b9e-a7e9-2523a4afe467"
  #define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

  bool BLEConnected = false;

  
  
  class MyCallbacks: public BLECharacteristicCallbacks {
   void onConnect(BLEServer* pServer) {
      BLEConnected = true;
      Serial.println("@ - Connected to device");
    };
 
    void onDisconnect(BLEServer* pServer) {
      BLEConnected = false;
      Serial.println("@ - Disconnected from device");
    }
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      
      if (value.length() > 0) {
      int requestedService = atoi(value.c_str());
      //Serial.println(requestedService);
      switch(requestedService) {
        //System Services
        case 10: service.ping(); break; //Service 10: Ping
        case 11: mainTokenStatus = true; break; //Service 11: Set Main BLE Token
        case 12: mainTokenStatus = false; break; //Service 12: Remove Main BLE Token
        case 19: ESP.restart(); break;//Service 19: Restart

        //Haptic Servies        
        case 20: service.set_haptor(0); break; //Service 20: Set Haptic Motor Off
        case 21: service.set_haptor(127); break; //Service 21: Set Haptic Motor -Half Power
        case 22: haptic_chime_start(); break;
        case 23: haptic_chime_stop(); break;
        case 24: haptic_chime_success(); break;
        case 25: haptic_chime_error(); break;

        //LED Services
        case 30: service.stop_LED(); break;
        case 31: service.set_red_LED(127); break;
        case 32: service.set_green_LED(127); break;
        case 33: service.set_blue_LED(127); break;
        case 34: service.set_cyan_LED(64); break;
        case 35: service.set_purple_LED(64); break;
        case 36: service.set_yellow_LED(64); break;
        case 37: service.set_white_LED(64); break;


        //Calibration Services
        case 40: calibrate_flex_sensor_range("outside"); break; //Service 40: Forced Calibration
        case 41: calibrate_flex_sensor_range("self"); break; //Service 41: Calibration condition-checked

        //Request Services
        //Service 50: Request Characteristics
        //Service 51: Request Main Object
        //Service 52: Request Flex Object
        //Service 53: Request IMU Object
        //Service 54: Request Push Button State
        //Service 55: Request Battery Estimate
        //Service 56: Request Parity Token
        //Service 57: Request LED-Haptic State


        //EEPROM Services 
       case 70: flashNVS();//Service 70: Flash EEPROM
        //Service 71: Dump EEPROM

        default: service.notifyError(); break;
      }

      }
    }
};






//FUNCTION DEFINITIONS

void set_pinModes() {
  //Input is Default, so no need to set those.
  pinMode(LED_red, OUTPUT);
  pinMode(LED_green, OUTPUT);
  pinMode(LED_blue, OUTPUT);
  pinMode(haptic_motor, OUTPUT);
  pinMode(RX_PIN, INPUT_PULLUP);
}

void buttonWait(){
  int buttonState = 0;
  while(1){
    buttonState = digitalRead(push_button);
    if (buttonState == HIGH) {
      return;
    }
  }
}
 
void setup() {
  Serial.begin(BAUD_RATE);
  set_pinModes();  
  
  boot_LED_haptic_routine(); 
  //buttonWait();
  calibrate_flex_sensor_range("self"); 
  setup_bluetooth();
  setup_accelerometer();
  service.set_purple_LED(64);
}
 
void loop() {
  
  if (mainTokenStatus) {
    set_accelerometer_data();
    set_flex_data();
    set_pushbutton_data();

    String ObjectToPush;

    ObjectToPush = "WAV-R-MO-";

    ObjectToPush += pushButtonStringify();

    ObjectToPush += flexStringify(gloveDataObject.right_thumb_angle);
    ObjectToPush += flexStringify(gloveDataObject.right_index_angle);
    ObjectToPush += flexStringify(gloveDataObject.right_middle_angle);
    ObjectToPush += flexStringify(gloveDataObject.right_ring_angle);
    ObjectToPush += flexStringify(gloveDataObject.right_fifth_angle);

    ObjectToPush += "EOM";
  
    std::string value = ObjectToPush.c_str();
    pCharacteristic->setValue(value);
    pCharacteristic->notify();
  }

  delay(100);
}
