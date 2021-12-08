#include <LiquidCrystal.h>
#include"Memory.h"
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
  //enterPlayerName();
  //playAgain();
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
void writePlayerName(){
  if(currentLetterPosition >= alphabetLength){
     currentLetterPosition = 0;
  }else if(currentLetterPosition < 0){
    currentLetterPosition = alphabetLength - 1;
  }
  if(currentPlayerNamePosition >= 4){
     currentPlayerNamePosition = 0;
  }else if(currentPlayerNamePosition < 0){
    currentPlayerNamePosition = 3;
  }
  player[currentPlayerNamePosition] = alphabet[currentLetterPosition];
  updatePlayerName(player);
}
void changePlayerName(){
     if(ifJoystickMovedUp()){
        currentLetterPosition++;
        writePlayerName();
     }else if(ifJoystickMovedDown()){
        currentLetterPosition--;
        writePlayerName();
     }else if(ifJoystickMovedRight()){
        currentPlayerNamePosition++;
        writePlayerName();
     }else if(ifJoystickMovedLeft()){
        currentPlayerNamePosition--;
        writePlayerName();
     }else if(ifJoystickPressed){
        // write to EEPROM 
        saveHighScore(points, player);
        playAgain();
     }
}
void answerPlayAgain(){
  if(ifJoystickMovedUp() || ifJoystickMovedDown() || ifJoystickMovedRight() || ifJoystickMovedLeft()){
    playAgainScreen = false;
    enteringPlayerName = false;
    gameHasStarted = true;
    start();
    game();
    resetGame();
  }else if(ifJoystickPressed()){
    playAgainScreen = false;
    enteringPlayerName = false;
    mainMenuOpened = true;
    mainMenu();
    updateMainMenu();
  }
}
void loop() {
  readFromJoystick();
   /*if(millis() - lastMoved > moveMenuInterval){
     //changePlayerName();
     //answerPlayAgain();
     lastMoved = millis();
    }*/
  if(!gameHasStarted){
    // menu && settings
    if(millis() - lastMoved > moveMenuInterval){
     connectMenus();
     lastMoved = millis();
    }
  }else{
    if(enteringPlayerName){
      //we have a new high score
      changePlayerName(); 
    }else if(playAgainScreen){
      //game over
      //play again or go to menu
      answerPlayAgain();
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
