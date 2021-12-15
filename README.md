# :snake: Snake :snake:
### Snake game using Arduino UNO and 8x8 led matrix
:robot: [Introduction to Robotics](https://www.facebook.com/unibuc.robotics) @Unibuc 

### :books: [Project requirements](https://github.com/DimaOanaTeodora/Snake-game/edit/main/REQUIREMENTS.md) 

### <a href="http://stackoverflow.com" target="_blank">Watch YouTube demo here</a>

# How to play the game?
## Game goal
Goal is to eat the food and get a new high score. 
The game ends when the snake eats himself or collides with the obstacles/walls.

## Menu
You can scroll through the menus moving the joystcik up/down.
You can choose an option from the menu moving the joystick right. Menu design:
```
- MAIN MENU
  - START - choose to start the game
  - HIGH SCORE
  - SETTINGS (MENU)
      - DIFFICULTY
        - LOW/MEDIUM/HIGH
      - SOUND
       - MUTE/UNMUTE
      - LCD CONTRAST 
        - 1/2/3
      - LCD BRIGHTNESS
        - 1/2/3
      - MATRIX BRIGHTNESS 
        - 1/2/3
      - BACK (TO MAIN MENU)
  - ABOUT 
```

## Score and difficulty
```
The score depends on the difficulty:
 - LOW: 1 point/level
 - MEDIUM: 2 points/level
 - HIGH: 5 points/level
```

The movement speed of the snake increases once at 4 levels. In case of a new high score beeing reached, the player name and the score are written into the EEPROM memory of Arduino.

# App flow

![Snake](https://user-images.githubusercontent.com/61749814/146158283-e37aeae6-5790-430e-a6de-86c14bdb5b1d.png)

# Quick rundown

1.564 / 5.000
The application is divided into 14 headers, each corresponding to a part of the game.

When Arduino is starting, the EEPROM values are loaded for: LCD brightness, LCD contrast, matrix brightness, mute/unmute the sound and game difficulty level. A welcome message will appear on the screen for ```1.5s``` and after that, the main menu is loaded on the LCD.
The joystick input values are read continuously in ```loop()``` through ```readFromJoystick();``` method. There are 5 functions designed to test the direction of the joystick during the game in ```Joystick.h``` file.
The delay(millis); function is used only when the game blocking is necessary: the automatic scrolling in the ABOUT and HIGH SCORE submenus. The rest of the application uses the millis(); function, along with different values: 0,15s for food blinking, 0,5s for heart animation, 0,25s for menu movement, 0,11s for the initial speed of the snake. 
```C++
Utility.h
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
```

Several boolean variables ensure the interchanging between LCD screens: congratsHighScoreScreen, congratsScreen, playAgainScreen, gameHasStarted, mainMenuOpened, subMainMenuOpened, animationHeart, settingsMenuOpened, subSettingsMenuOpened. For each part of the menu that requires scrolling (horizontal or vertical) there is a function called changeX(value);, where X is the name of the screen that it corresponds, through which the new value is displayed. So, only one part of the screen is rendered each time, not the entire LCD. 
