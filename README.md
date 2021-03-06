# :snake: Snake :snake:
### Snake game using Arduino UNO and 8x8 led matrix
[Introduction to Robotics](https://www.facebook.com/unibuc.robotics) @Unibuc 

### :weight_lifting_woman: [How to play the game](https://github.com/DimaOanaTeodora/Snake-game#how-to-play-the-game)

### :books: [Project requirements](https://github.com/DimaOanaTeodora/Snake-game/edit/main/REQUIREMENTS.md) 

### :clapper: <a href="https://youtu.be/FP7H6eIXJGc" target="_blank">Watch YouTube demo here</a>

### :eyeglasses: [Go to documentation](https://github.com/DimaOanaTeodora/Snake-game/blob/main/README.md#world_map-app-flow)

![IMG_20211219_140929](https://user-images.githubusercontent.com/61749814/146675184-b05238be-debe-4a58-8bef-d56f41417a2d.jpg)

# How to play the game?

## :weight_lifting_woman: Game goal
Goal is to eat the food and get a new high score. The game ends when the snake eats himself or collides with the obstacles/walls.

## :gear: Menu
You can scroll through the menus moving the joystcik up/down. You can choose an option from the menu moving the joystick right. Menu design:
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

The movement speed of the snake increases once at 4 levels. In case of a new high score beeing reached, the player name and the score are written into the EEPROM memory of Arduino. You can see them in the Main menu -> HIGH SCORE section.

# :world_map: App flow

![Snake](https://user-images.githubusercontent.com/61749814/146158283-e37aeae6-5790-430e-a6de-86c14bdb5b1d.png)

# :building_construction:	 Quick rundown

Hardware components:
- Arduino UNO
- 16x2 LCD
- joystick
- active buzzer 
- 8x8 led matrix
- two breadboards
- wires
- 10UF electrolytic capacitor
- 100UF electrolytic capacitor
- 0.033UF ceramic capacitor
- 10k resistor

The application is divided into 14 headers, each corresponding to a part of the game.

When Arduino is starting, the EEPROM values are loaded for: LCD brightness, LCD contrast, matrix brightness, mute/unmute the sound and game difficulty level. A welcome message will appear on the screen for ```1.5s``` and after that, the main menu is loaded on the LCD.
The joystick input values are read continuously in ```loop()``` through ```readFromJoystick();``` method. There are 5 functions designed to test the direction of the joystick during the game in ```Joystick.h``` file.
The ```delay(millis);``` function is used only when the game blocking is allowed: the automatic scrolling in the ABOUT and HIGH SCORE sections. The rest of the application uses the ```millis();``` function, along with different values: ```0.15s``` for food blinking, ```0.5s``` for heart animation, ```0.25s``` for menu movement, ```0.11s``` for the initial speed of the snake. 

```C++
Utility.h

void changeState() {
  // changing states during the entire app
  if (!gameHasStarted) {
    // menu && settings
    if (millis() - lastMoved > moveMenuInterval) {
      connectMenus();
      lastMoved = millis();
    }
  } else {
    if (congratsScreen) {
      //the game is over but we don't have a new high score
      switchHeart();
      if (millis() - lastMoved > moveMenuInterval) {
        exitCongratsScreen();
        lastMoved = millis();
      }
    } else if (congratsHighScoreScreen) {
      //the game is over && we have a new high score
      switchHeart();
      if (millis() - lastMoved > moveMenuInterval) {
        exitCongratsHighScoreScreen();
        lastMoved = millis();
      }
    } else if (enteringPlayerName) {
      //we have a new high score
      if (millis() - lastMoved > moveMenuInterval) {
        changePlayerName();
        lastMoved = millis();
      }
    } else if (playAgainScreen) {
      //game over
      //play again or go to menu
      if (millis() - lastMoved > moveMenuInterval) {
        answerPlayAgain();
        lastMoved = millis();
      }
    } else {
      // during the game
      blinkingFood();
      if (millis() - lastMoved > moveGameInterval) {
        updateSnakePosition();
        showSnake();
        lastMoved = millis();
      }
    }
  }
}
```

Several boolean variables ensure the interchanging between LCD screens and game states: ```congratsHighScoreScreen, congratsScreen, playAgainScreen, gameHasStarted, mainMenuOpened, subMainMenuOpened, animationHeart, settingsMenuOpened, subSettingsMenuOpened```. For each part of the menu that requires scrolling (horizontal or vertical) there is a function called ```changeX(value);```, where ```X``` is the name of the screen that it corresponds, through which the new value is displayed. So, only one part of the screen is rendered each time, not the entire LCD. 

The snake is saved into two arrays, one for the row coordinates and one for the column coordinates: ```snakeRow``` and ```snakeCol```. The initial length is 2, and the head is random generated. The head is on the last position of the arrays(```snakeLength - 1```) and the tail is on the first position. 

The snake is moved on the game board as follows: 
1. ```updateSnakePosition()``` - calculates the next row/column on the board depending on the joystick input
2. ```moveGame(nextPosition, directionRow)``` - checks if it has food to eat and if the snake is dead
3. ```moveTheSnake(nextPosition, directionRow)``` - calculates the new coordinates for the snake

 ```nextPosition``` represents the next row if the ```directionRow``` is ```true```, or the next column if the ```directionRow``` is ```false```.
 
When a food is eaten, the length of the snake is increased by one unit and the new tail is generated by the method below:

```C++
GamePlay.h

void updateSnake() {
  ...
  
  snakeLength ++;
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeRow[i] = snakeRow[i - 1];
    snakeCol[i] = snakeCol[i - 1];
  }

  tailRow = snakeRow[1];
  tailCol = snakeCol[1];
  tailRow2 = snakeRow[2];
  tailCol2 = snakeCol[2];

  if (tailRow2 == tailRow) {
    if (tailCol < tailCol2) {
      // right
      snakeRow[0] = tailRow;
      tailCol --;
      if (tailCol < minMatrixValue) {
        tailCol = maxMatrixValue;
      }
      snakeCol[0] = tailCol;
    } else {
      // left
      snakeRow[0] = tailRow;
      tailCol ++;
      if (tailCol > maxMatrixValue) {
        tailCol = minMatrixValue;
      }
      snakeCol[0] = tailCol;
    }
  } else if (tailCol2 == tailCol) {
    if (tailRow < tailRow2) {
      // under
      tailRow --;
      if (tailRow < minMatrixValue) {
        tailRow = maxMatrixValue;
      }
      snakeRow[0] = tailRow;
      snakeCol[0] = tailCol;
    } else {
      // above
      tailRow ++;
      if (tailRow > maxMatrixValue) {
        tailRow = minMatrixValue;
      }
      snakeRow[0] = tailRow;
      snakeCol[0] = tailCol;
    }
  }
}
```
 Game levels:

 1. LOW: no walls, just random generated food/level 
 2. MEDIUM: random 4/3 walls generated at level 1 and random generated food/level
 3. HIGH: fixed corner walls nd random generated food/level

LOW <img src="https://user-images.githubusercontent.com/61749814/146180742-d7227f5d-96ed-409d-8f4a-d6e00314e4e0.png" width="100px" height="100px"/>MEDIUM <img src="https://user-images.githubusercontent.com/61749814/146180695-9de9b27a-03ec-4371-b168-8e1205f3a50a.png" width="100px" height="100px"/>HIGH <img src="https://user-images.githubusercontent.com/61749814/146180628-cf052a75-7d3d-4c60-b5f3-39ee77e6e5a5.png" width="100px" height="100px"/>
 
The walls, food and the head snake are random generated using ```random(minInterval, maxInterval);``` and ```randomSeed(analogread(0));```, because it's important for a sequence of values generated by ```random()``` to differ at the beginning of each new game.

The game saves the last 3 high scores along with the player's nicknames (maximum 4 letters/nickname). These are displayed in the Main menu -> HIGH SCORE section. It also saves the LCD contrast/brightness, sound, difficulty level and matrix settings from the settings menu in the EEPROM memory, so that they can be loaded when the Arduino board is restarted.

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
 
 Matrix animations
 Each matrix animation displayed is defined as an array of bytes (ex: ``` three[] = {B00000000, B00111100, B00100000, B00111000, B00100000, B00100100, B00111100, B00000000}; ```). During the game the ```updateMatrixDisplay(const byte matrix[]);``` function is called for displaying the animations on the matrix.
 
 ```C++
 Matrix.h
 
 void updateMatrixDisplay(const byte matrix[]) {
  // show the icons on the matrix display
  lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, matrix[row]);
  }
}
 ```
 
 1. Geeting message

<img src="https://user-images.githubusercontent.com/61749814/146815185-93da275d-0b51-4484-a1ba-6bd427047256.png" width="100px" height="100px"/>

2. Moving through the menu

<img src="https://user-images.githubusercontent.com/61749814/146815392-9ece843a-60b4-4034-aedb-a02e2182e0a4.png" width="100px" height="100px"/><img src="https://user-images.githubusercontent.com/61749814/146817994-e3dab984-aaa3-4ec1-8ef4-aa51da95555e.png" width="100px" height="100px"/><img src="https://user-images.githubusercontent.com/61749814/146818033-88be8840-b754-45e0-ada4-6adcc7dd9c2e.png" width="100px" height="100px"/><img src="https://user-images.githubusercontent.com/61749814/146818064-36b35b67-6846-4bee-a3a8-6292ff89297b.png" width="100px" height="100px"/>

3. Starting a game

GAME <img src="https://user-images.githubusercontent.com/61749814/146816185-b9445d7e-96ed-45d0-adfd-d4cefa770b44.png" width="100px" height="100px"/>
SET <img src="https://user-images.githubusercontent.com/61749814/146815932-68858b4d-3005-4b50-bc51-5dbe33c1f948.png" width="100px" height="100px"/>
GO! <img src="https://user-images.githubusercontent.com/61749814/146815680-a0cc323e-e574-47da-8bb5-4a2e5cbe0d9d.png" width="100px" height="100px"/>

4. Game over

<img src="https://user-images.githubusercontent.com/61749814/146816467-5c575795-8f47-4032-9318-442402e138b6.png" width="100px" height="100px"/><img src="https://user-images.githubusercontent.com/61749814/146817018-10a09f7e-a974-4f10-a9fc-4a0d7f8bcb9b.png" width="100px" height="100px"/>

5. Start again?

<img src="https://user-images.githubusercontent.com/61749814/146817188-8653f473-5cbe-4d84-9b32-528fd75183c4.png" width="100px" height="100px"/>


