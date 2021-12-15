unsigned int long long lastMoved = 0;
unsigned int long long lastMoved2 = 0;
unsigned int long long lastMoved3 = 0;
const int moveMenuInterval = 250;
const int switchHeartInterval = 500;
const int blinkingFoodInterval = 150;

bool blinking = false;

void exitCongratsHighScoreScreen() {
  // the game is over
  // we have a new high score => switch to enter the player name screen
  if(joystickMovedUp() || joystickMovedDown() || joystickMovedRight() || joystickMovedLeft()) {
    menuSound();
    congratsHighScoreScreen = false;
    enterPlayerName();
  }
}
void exitCongratsScreen() {
  // the game is over
  // we don't have a new high score => switch play again screen
  if(joystickMovedUp() || joystickMovedDown() || joystickMovedRight() || joystickMovedLeft()) {
    menuSound();
    congratsScreen = false;
    playAgainScreen = true;
    playAgain();
  }
}
void answerPlayAgain() {
  // the game is over
  // answer to play again screen
  if(joystickMovedUp() || joystickMovedDown() || joystickMovedRight() || joystickMovedLeft()) {
    menuSound();
    playAgainScreen = false;
    enteringPlayerName = false;
    gameHasStarted = true;
    start();
    game();
    resetGame();
  }else if(joystickPressed()) {
    menuSound();
    playAgainScreen = false;
    enteringPlayerName = false;
    gameHasStarted = false;
    mainMenuOpened = true;
    mainMenu();
    updateMainMenu();
  }
}
void connectMenus() {
  // switch between the main menu and the settings menu
  if(mainMenuOpened) {
    updateMainMenu();
  }else if(settingsMenuOpened) {
    if(joystickMovedRight() && subSettingsMenuOpened == false && currentSettingsMenu == maxValueSettingsMenu) {
        back();
        mainMenu();
    }else{
      updateSettingsMenu();
    }
  }
}
void switchHeart() {
  // changing heart animation
  if(millis() - lastMoved2 > switchHeartInterval) {
       animation();
       lastMoved2 = millis();
  }
}
void blinkingFood() {
   if( millis() - lastMoved3 > blinkingFoodInterval) {
       showFood(blinking);
       blinking = !blinking; 
       lastMoved3 = millis();
  }
}
void changeState() {
  // changing states during the entire app
  if(!gameHasStarted) {
    // menu && settings
    if(millis() - lastMoved > moveMenuInterval) {
     connectMenus();
     lastMoved = millis();
    }
  }else {
    if(congratsScreen) {
      //the game is over but we don't have a new high score
      switchHeart(); 
      if(millis() - lastMoved > moveMenuInterval) {
       exitCongratsScreen(); 
       lastMoved = millis();
      }
    }else if(congratsHighScoreScreen) {
      //the game is over && we have a new high score
      switchHeart();
      if(millis() - lastMoved > moveMenuInterval) {
       exitCongratsHighScoreScreen(); 
       lastMoved = millis();
      }
    }else if(enteringPlayerName) {
      //we have a new high score
      if(millis() - lastMoved > moveMenuInterval) {
       changePlayerName(); 
       lastMoved = millis();
      }
    }else if(playAgainScreen) {
       //game over
       //play again or go to menu
       if(millis() - lastMoved > moveMenuInterval) {
       answerPlayAgain(); 
       lastMoved = millis();
      }
    }else{
      // during the game
      blinkingFood();
      if(millis() - lastMoved > moveGameInterval) {
       updateSnakePosition();
       showSnake();
       lastMoved = millis();
      }
    }
  }
}
