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

byte matrixByte[matrixSize] = {
  B00000000,
  B00011000,
  B00111100,
  B01111110,
  B01111110,
  B01111110,
  B01101110,
  B00000000
}; 
unsigned int long long lastMoved = 0;
const int moveMenuInterval = 250;
const int moveGameInterval = 100;

void setup() {
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
  
  analogWrite(contrastPin, contrastValue);
  analogWrite(brightnessPin, brightnessValue); 
  
  //updateMatrixDisplay(matrixByte);
  //resetMemory();
  greetings();
  mainMenu();
  Serial.begin(9600);
}
void answerPlayAgain(){
  if(joystickMovedUp() || joystickMovedDown() || joystickMovedRight() || joystickMovedLeft()){
    playAgainScreen = false;
    enteringPlayerName = false;
    gameHasStarted = true;
    start();
    game();
    resetGame();
  }else if(joystickPressed()){
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
void changeState(){
  if(!gameHasStarted){
    // menu && settings
    if(millis() - lastMoved > moveMenuInterval){
     connectMenus();
     lastMoved = millis();
    }
  }else{
    if(enteringPlayerName){
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
      if(millis() - lastMoved > moveGameInterval){
       updateSnakePosition();
       showSnake();
       lastMoved = millis();
      }
    }
  }
}
void loop() {
  //tone(A2, 200, 500);
  readFromJoystick();
  
  changeState();
}
