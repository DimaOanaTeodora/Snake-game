int moveGameInterval = 150;
bool congratsHighScoreScreen = false;
bool congratsScreen = false;
bool playAgainScreen = false;

// -1 left, 1 right, 2 up, -2 down
int snakeDirection = 0;

// HIGH SCORE -> PLAYER
String player = "____";
const String alphabet = "abcdefghijklmnopqrstuvwxyz";
const byte maxLetterPosition = alphabet.length() - 1;
const byte minLetterPosition = 0;
int currentLetterPosition = 0;
int currentNamePosition = 0;
bool enteringPlayerName = false;
const byte maxNamePosition = 3;
const byte minNamePosition = 0;

const int maxMatrixValue = 7;
const int minMatrixValue = 0;

void writePlayerName() {
  if (currentLetterPosition > maxLetterPosition) {
    currentLetterPosition = minLetterPosition;
  } else if (currentLetterPosition < minLetterPosition) {
    currentLetterPosition = maxLetterPosition;
  }

  if (currentNamePosition > maxNamePosition) {
    currentNamePosition = minNamePosition;
  } else if (currentNamePosition < minNamePosition) {
    currentNamePosition = maxNamePosition;
  }
  player[currentNamePosition] = alphabet[currentLetterPosition];
  updatePlayerName(player);
}
void changePlayerName() {
  if (joystickMovedUp()) {
    menuSound();
    currentLetterPosition++;
    writePlayerName();
  } else if (joystickMovedDown()) {
    menuSound();
    currentLetterPosition--;
    writePlayerName();
  } else if (joystickMovedRight()) {
    menuSound();
    currentNamePosition++;
    writePlayerName();
  } else if (joystickMovedLeft()) {
    menuSound();
    currentNamePosition--;
    writePlayerName();
  } else if (joystickPressed()) {
    menuSound();
    // write to EEPROM
    saveHighScore(points, player);
    enteringPlayerName = false;
    playAgain();
  }
}
void resetGame() {
  lc.clearDisplay(0);
  enteringPlayerName = false;
  level = 1;
  points = 0;
  moveGameInterval = 150;
  snakeDirection = 0;
  game(); //reset LCD

  // generate obstacles depending on the level
  switch (difficultyLevel) {
    case 1:
      numberOfWalls = 0;
      break;
    case 2:
      tinyObstacles();
      showWalls();
      break;
    case 3:
      cornerWalls();
      showWalls();
      break;
  }
  generateSnake();
  generateFood();
  showSnake();
  showFood(true);
}
void moveTheSnake(int newValue, bool row) {
  // move the snake by changing head position
  // newValue is the new row/column for the head

  bodyRow = snakeRow[snakeLength - 2];
  bodyCol = snakeCol[snakeLength - 2];

  // this condition doesn't let the snake to turn the head 180 degrees and suicide
  if (!((!row && abs(bodyCol - newValue) == 0) || (row && abs(bodyRow - newValue) == 0))) {
    tailRow = snakeRow[0];
    tailCol = snakeCol[0];

    // teleporting the snake through the walls
    if (newValue > maxMatrixValue) {
      newValue = minMatrixValue;
    } else if (newValue < minMatrixValue) {
      newValue = maxMatrixValue;
    }

    for (int i = 0; i < snakeLength; i++) {
      if (i == snakeLength - 1) {
        // Snake HEAD
        if (row) {
          snakeRow[i] = newValue;
        } else {
          snakeCol[i] = newValue;
        }
      } else {
        snakeRow[i] = snakeRow[i + 1];
        snakeCol[i] = snakeCol[i + 1];
      }
    }
  }
}
void updateSnake() {
  // increase the size of the snake with 1 point attached to the tail
  int tailRow2, tailCol2;

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
void increaseGameSpeed() {
  // increase the speed depending on the level 4,8,12, 16
  if (level % 4 == 0) {
    moveGameInterval = moveGameInterval - 20;
  }
}
void eatFood() {
  headRow = snakeRow[snakeLength - 1];
  headCol = snakeCol[snakeLength - 1];

  if (headRow == foodRow && headCol == foodCol) {
    eatSound();
    if (difficultyLevel == 3) {
      points += 5;
    } else if (difficultyLevel == 2) {
      points += 2;
    } else {
      points ++;
    }
    level ++;
    increaseGameSpeed();
    updateGame(level, points);//update LCD with score
    // generate new food && new snake
    updateSnake();
    generateFood();
  }
}
bool dead() {
  // true if the snake hit a wall or committed suicide
  headRow = snakeRow[snakeLength - 1];
  headCol = snakeCol[snakeLength - 1];

  // suicide
  for (int i = 0; i < snakeLength - 1; i++) {
    if (snakeCol[i] == headCol && snakeRow[i] == headRow) {
      return true;
    }
  }
  // hit a wall
  for (int i = 0; i < numberOfWalls; i++) {
    if (wallsRow[i] == headRow && wallsCol[i] == headCol) {
      return true;
    }
  }
  return false;
}
void gameOver() {
  playAgainScreen = true;
  if (points > EEPROM.read(5)) {
    // we have a new high score
    congratsHighScore(points);
    congratsHighScoreScreen = true;
    enteringPlayerName = true;
    congratsHighScore(points);
  } else {
    congratsScreen = true;
    congrats(points);
  }
}
void moveGame(int nextPosition, bool directionRow) {
  moveTheSnake(nextPosition, directionRow);
  lc.setLed(0, tailRow, tailCol, false);
  eatFood();
  if (dead()) {
    colisionSound();
    gameOver();
  }
}
void updateSnakePosition() {
  // move the snake one position on the board
  if (snakeDirection != -2 && joystickMovedUp()) {
    // if the snake move in a direction it doesn't move in the oposite direction
    snakeDirection = 2;
    moveGame(snakeRow[snakeLength - 1] + 1, true);
  } else if (snakeDirection != 2 && joystickMovedDown()) {
    snakeDirection = -2;
    moveGame(snakeRow[snakeLength - 1] - 1, true);
  } else if (snakeDirection != -1 && joystickMovedRight()) {
    snakeDirection = 1;
    moveGame(snakeCol[snakeLength - 1] - 1, false);
  } else if (snakeDirection != 1 && joystickMovedLeft()) {
    snakeDirection = -1;
    moveGame(snakeCol[snakeLength - 1] + 1, false);
  } else if (snakeDirection != 0) {
    if (snakeDirection == -1) {
      //continuously move the snake to the left
      moveGame(snakeCol[snakeLength - 1] + 1, false);
    } else if (snakeDirection == 1) {
      //continuously move the snake to the right
      moveGame(snakeCol[snakeLength - 1] - 1, false);
    } else if (snakeDirection == 2) {
      //continuously move the snake up
      moveGame(snakeRow[snakeLength - 1] + 1, true);
    } else if (snakeDirection == -2) {
      //continuously move the snake down
      moveGame(snakeRow[snakeLength - 1] - 1, true);
    }
  }
}
