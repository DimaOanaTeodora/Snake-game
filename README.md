# :snake: Snake :snake:
### Snake game using Arduino UNO and 8x8 led matrix
[Introduction to Robotics](https://www.facebook.com/unibuc.robotics) @Unibuc 

### :books: [Project requirements](https://github.com/DimaOanaTeodora/Snake-game/edit/main/REQUIREMENTS.md) 

### <a href="http://stackoverflow.com" target="_blank"> :clapper: Watch YouTube demo here</a>

# :crossed_swords: How to play the game?

## :weight_lifting_woman: Game goal
Goal is to eat the food and get a new high score. 
The game ends when the snake eats himself or collides with the obstacles/walls.

## :gear: Menu
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

## :balance_scale: Score and difficulty
```
The score depends on the difficulty:
 - LOW: 1 point/level
 - MEDIUM: 2 points/level
 - HIGH: 5 points/level
```

The movement speed of the snake increases once at 4 levels. In case of a new high score beeing reached, the player name and the score are written into the EEPROM memory of Arduino.

# :world_map: App flow

![Snake](https://user-images.githubusercontent.com/61749814/146158283-e37aeae6-5790-430e-a6de-86c14bdb5b1d.png)

# :building_construction:	 Quick rundown
The application is divided into 14 headers, each corresponding to a part of the game.

When Arduino is starting, the EEPROM values are loaded for: LCD brightness, LCD contrast, matrix brightness, mute/unmute the sound and game difficulty level. A welcome message will appear on the screen for ```1.5s``` and after that, the main menu is loaded on the LCD.
The joystick input values are read continuously in ```loop()``` through ```readFromJoystick();``` method. There are 5 functions designed to test the direction of the joystick during the game in ```Joystick.h``` file.
The ```delay(millis);``` function is used only when the game blocking is allowed: the automatic scrolling in the ABOUT and HIGH SCORE submenus. The rest of the application uses the ```millis();``` function, along with different values: ```0.15s``` for food blinking, ```0.5s``` for heart animation, ```0.25s``` for menu movement, ```0.11s``` for the initial speed of the snake. 
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

Several boolean variables ensure the interchanging between LCD screens: ```congratsHighScoreScreen, congratsScreen, playAgainScreen, gameHasStarted, mainMenuOpened, subMainMenuOpened, animationHeart, settingsMenuOpened, subSettingsMenuOpened```. For each part of the menu that requires scrolling (horizontal or vertical) there is a function called ```changeX(value);```, where X is the name of the screen that it corresponds, through which the new value is displayed. So, only one part of the screen is rendered each time, not the entire LCD. 

The snake is saved in two arrays, one for the row coordinates and one for the column coordinates: ```snakeRow``` and ```snakeCol```. The initial length is 2, and the head is generated randomly. The head is on the last position of the arrays(```snakeLength - 1```) and the tail is on the first position. 


The snake is moved on the game board as follows: 
1. updateSnakePosition() - calculates the next row/column on the board depending on the joystick input
2. moveGame(nextPosition, directionRow) - checks if it has food to eat and if the snake is dead
3. moveTheSnake(nextPosition, directionRow) - calculates the new coordinates for the snake

 ```nextPosition``` represents the next row if the ```directionRow``` is ```true```, or the next column if the ```directionRow``` is ```false```
 
When a food is eaten, the length of the snake is increased by one unit and the new tail is generated by the function below:
```C++
GamePlay.h

void updateSnake() {
  ...
  
  snakeLength ++;
  for(int i = snakeLength-1; i > 0; i--) {
    snakeRow[i] = snakeRow[i - 1];
    snakeCol[i] = snakeCol[i - 1];
  }

  tailRow = snakeRow[1];
  tailCol = snakeCol[1];
  tailRow2 = snakeRow[2];
  tailCol2 = snakeCol[2];

  if(tailRow2 == tailRow) {
    if(tailCol < tailCol2) {
      // right
      snakeRow[0] = tailRow;
      tailCol --;
      if(tailCol < minMatrixValue) {
        tailCol = maxMatrixValue;
      }
      snakeCol[0] = tailCol;
    }else{
      // left
      snakeRow[0] = tailRow;
      tailCol ++;
      if(tailCol > maxMatrixValue) {
        tailCol = minMatrixValue;
      }
      snakeCol[0] = tailCol;
    }
  }else if(tailCol2 == tailCol) {
    if(tailRow < tailRow2) {
      // under
      tailRow --;
      if(tailRow < minMatrixValue) {
        tailRow = maxMatrixValue;
      }
      snakeRow[0] = tailRow;
      snakeCol[0] = tailCol;
    }else{
      // above
      tailRow ++;
      if(tailRow > maxMatrixValue) {
        tailRow = minMatrixValue;
      }
      snakeRow[0] = tailRow;
      snakeCol[0] = tailCol;
    }
  }
}
```
 Game levels:

 1. LOW: no walls, just randomly generated food/leve 
 2. MEDIUM: random 4/3 walls generated at level 1 and randomly generated food/level
 3. HIGH: fixed corner walls nd randomly generated food/level

 1. <img src="https://user-images.githubusercontent.com/61749814/146180742-d7227f5d-96ed-409d-8f4a-d6e00314e4e0.png" width="100px" height="100px"/>2. <img src="https://user-images.githubusercontent.com/61749814/146180695-9de9b27a-03ec-4371-b168-8e1205f3a50a.png" width="100px" height="100px"/>3. <img src="https://user-images.githubusercontent.com/61749814/146180628-cf052a75-7d3d-4c60-b5f3-39ee77e6e5a5.png" width="100px" height="100px"/>
 
 The walls, food and head snake are random generated using a custom random function because of a Arduino bug - [find out more about that here](https://forum.arduino.cc/t/help-random-function-not-working/3183/3): 
 ```C++
 Objects.h
 
 unsigned int newRandom(unsigned int minimum, unsigned int maximum){
  // Arduino bug: the random(x,y) function doesn't work properly
  return minimum + random() % (maximum - minimum);
}
 ```
The game svaes the last 3 high scores along with the player's nickname (maximum 4 letters). These are displayed in the main menu -> HIGH SCORE. It also saves the LCD, sound, difficulty and matrix settings from the settings menu in the EEPROM memory, so that they can be loaded when the Arduino board is restarted.

EEPROM schema

<img src="https://user-images.githubusercontent.com/61749814/146183805-7ce1380d-3f0b-4078-ae13-3b3d5f5822a7.png" width="700px" height="350px"/>
 
 The new values of the name and the high score are saved in the EEPROM by shifting the memory byte by byte to make room for the new values.
 ```C++
 Memory.h
 
 void writeNewStringNameToEEPROM(String player1) {
  ...
  
  // player1's name
  for (int i = 0; i < len1; i++) {
      EEPROM.update(11 + i, player1[i]);
  } 
  // player2's name
  for (int i = 0; i < len2; i++) {
      EEPROM.update(11 + len1 + i, player2[i]);
  }
  // player3's name
  for (int i = 0; i < len3; i++) {
      EEPROM.update(11 + len1 + len2 + i, player3[i]);
  }
}
 ```
