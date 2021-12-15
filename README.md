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

