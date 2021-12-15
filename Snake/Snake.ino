#include"Memory.h"
#include"Matrix.h"
#include"Sound.h"
#include"LCD.h"
#include"Joystick.h"
#include"Objects.h"
#include"ShowObjects.h"
#include"GamePlay.h"
#include"SubSettingsMenus.h"
#include"SettingsMenu.h"
#include"SubMainMenus.h"
#include"MainMenu.h"
#include"Utility.h"

void setup() {
  //resetMemory();
  // read the settings from EEPROM
  difficultyLevel = EEPROM.read(0);
  int sound = EEPROM.read(1);
  if(sound == 1) {
    mute = false;
  }else {
    mute = true;
  }
  contrastLevel = EEPROM.read(2);
  brightnessLevel = EEPROM.read(3);
  matrixIntensityLevel = EEPROM.read(4);
  
  lc.shutdown(0, false); 
  lc.setIntensity(0, matrixIntensityValue + matrixIntensityLevel);
  lc.clearDisplay(0);
  pinMode(RS, OUTPUT);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(pinSw, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  analogWrite(contrastPin, contrastValue + contrastLevel * 16);
  analogWrite(brightnessPin, brightnessValue + brightnessLevel * 100); 
  
  greetings();
  mainMenu();
  Serial.begin(9600);
}
void loop() {
  readFromJoystick();
  changeState();
}
