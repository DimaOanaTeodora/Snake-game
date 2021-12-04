#include <LiquidCrystal.h>
#include"Matrix.h"
#include"Sound.h"
#include"LCD.h"
#include"Joystick.h"
#include"GamePlay.h"
#include"SubSettingsMenus.h"
#include"SettingsMenu.h"
#include"SubMainMenus.h"
#include"MainMenu.h"
byte matrixByte[matrixSize] = {
  B00000000,
  B00011000,
  B00111100,
  B01100110,
  B11000011,
  B10000001,
  B00000000,
  B00000000
}; 


void setup() {
  lc.shutdown(0, false); 
  lc.setIntensity(0, matrixIntensityValue + matrixIntensityLevel);
  lc.clearDisplay(0);
  
  pinMode(RS, OUTPUT);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(pinSw, INPUT_PULLUP);

  lcd.begin(16, 2);
  //lcd.clear();
  //lcd.setCursor(0, 0);
  
  analogWrite(contrastPin, contrastValue);
  analogWrite(brightnessPin, brightnessValue); 
  
  //updateMatrixDisplay(matrixByte);
  //greetings();
  mainMenu();
  
  Serial.begin(9600);
}

void connectMenus(){
  if(mainMenuOpened){
    updateMainMenu();
  }else if(settingsMenuOpened){
    if(ifJoystickMovedRight() && subSettingsMenuOpened == false && currentSettingsMenu == 5){
        back();
        mainMenu();
    }else{
      updateSettingsMenu();
    }
  }
}
void loop() {
  
  readFromJoystick();
  
  connectMenus();
  
  delay(250); 
}
