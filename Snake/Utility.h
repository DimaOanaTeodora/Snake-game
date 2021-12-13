// Variables
unsigned int long long lastMoved = 0;
unsigned int long long lastMoved2 = 0;
unsigned int long long lastMoved3 = 0;
const int moveMenuInterval = 250;
const int switchHeartInterval = 500;
const int blinkingFoodInterval = 150;
bool blinking = false;

// Functions
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
