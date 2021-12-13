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

void setup() {
  //resetMemory();
  // read the settings from EEPROM
  difficultyLevel = EEPROM.read(0);
  int sound = EEPROM.read(1);
  if(sound == 1){
    mute = false;
  }else{
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
void exitCongratsHighScoreScreen(){
  if(joystickMovedUp() || joystickMovedDown() || joystickMovedRight() || joystickMovedLeft()){
    menuSound();
    congratsHighScoreScreen = false;
    enterPlayerName();
  }
}
void exitCongratsScreen(){
  if(joystickMovedUp() || joystickMovedDown() || joystickMovedRight() || joystickMovedLeft()){
    menuSound();
    congratsScreen = false;
    playAgainScreen = true;
    playAgain();
  }
}
void answerPlayAgain(){
  if(joystickMovedUp() || joystickMovedDown() || joystickMovedRight() || joystickMovedLeft()){
    menuSound();
    playAgainScreen = false;
    enteringPlayerName = false;
    gameHasStarted = true;
    start();
    game();
    resetGame();
  }else if(joystickPressed()){
    menuSound();
    playAgainScreen = false;
    enteringPlayerName = false;
    gameHasStarted = false;
    mainMenuOpened = true;
    mainMenu();
    updateMainMenu();
  }
}
void connectMenus(){
  if(mainMenuOpened){
    updateMainMenu();
  }else if(settingsMenuOpened){
    if(joystickMovedRight() && subSettingsMenuOpened == false && currentSettingsMenu == 5){
        back();
        mainMenu();
    }else{
      updateSettingsMenu();
    }
  }
}
void switchHeart(){
  if(millis() - lastMoved2 > switchHeartInterval){
       // changing heart animation
       animation();
       lastMoved2 = millis();
  }
}
bool blinking = false;
void blinkingFood(){
   if( millis() - lastMoved3 > blinkingFoodInterval){
       showFood(blinking);
       blinking = !blinking; 
       lastMoved3 = millis();
  }
}
void changeState(){
  if(!gameHasStarted){
    // menu && settings
    if(millis() - lastMoved > moveMenuInterval){
     connectMenus();
     lastMoved = millis();
    }
  }else{
    if(congratsScreen){
      //the game is over but we don't have a new high score
      switchHeart(); 
      if(millis() - lastMoved > moveMenuInterval){
       exitCongratsScreen(); 
       lastMoved = millis();
      }
    }else if(congratsHighScoreScreen){
      //the game is over && we have a new high score
      switchHeart();
      if(millis() - lastMoved > moveMenuInterval){
       exitCongratsHighScoreScreen(); 
       lastMoved = millis();
      }
    }else if(enteringPlayerName){
      //we have a new high score
      if(millis() - lastMoved > moveMenuInterval){
       changePlayerName(); 
       lastMoved = millis();
      }
    }else if(playAgainScreen){
       //game over
       //play again or go to menu
       if(millis() - lastMoved > moveMenuInterval){
       answerPlayAgain(); 
       lastMoved = millis();
      }
    }else{
      // during the game
      blinkingFood();
      if(millis() - lastMoved > moveGameInterval){
       updateSnakePosition();
       showSnake();
       lastMoved = millis();
      }
    }
  }
}
void loop() {
  readFromJoystick();
  
  changeState();
}
