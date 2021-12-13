// Variables
int moveGameInterval = 110;
bool congratsHighScoreScreen = false;
bool congratsScreen = false;

//Functions
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
     if(joystickMovedUp()){
        menuSound();
        currentLetterPosition++;
        writePlayerName();
     }else if(joystickMovedDown()){
        menuSound();
        currentLetterPosition--;
        writePlayerName();
     }else if(joystickMovedRight()){
        menuSound();
        currentPlayerNamePosition++;
        writePlayerName();
     }else if(joystickMovedLeft()){
        menuSound();
        currentPlayerNamePosition--;
        writePlayerName();
     }else if(joystickPressed()){
        menuSound();
        // write to EEPROM 
        saveHighScore(points, player);
        enteringPlayerName = false;
        playAgain();
     }
}
void resetGame(){
  lc.clearDisplay(0);
  enteringPlayerName = false;
  level = 1;
  points = 0; 
  moveGameInterval = 110;
  game(); //reset LCD

  // generate obstacles depending on the level
  switch(difficultyLevel){
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
void moveTheSnake(int newValue, bool row){
  // move the snake by changing head position
  // newValue is the new row/column for the head
 
  bodyRow = snakeRow[snakeLength - 2];
  bodyCol = snakeCol[snakeLength - 2];

  // this condition doesn't let the snake to turn the head 180 degrees and suicide
  if(!((!row && abs(bodyCol - newValue)==0) || (row && abs(bodyRow - newValue)==0))){
    tailRow = snakeRow[0];
    tailCol = snakeCol[0];
    
    // teleporting the snake through the walls
    if(newValue >= 8){
      newValue = 0;
    }else if(newValue <= -1){
      newValue = 7;
    }
  
    for(int i = 0; i < snakeLength; i++){
        if(i == snakeLength - 1){
          // Snake HEAD
          if(row){
            snakeRow[i] = newValue;
          }else{
            snakeCol[i] = newValue;
          }
        }else{
          snakeRow[i] = snakeRow[i + 1];
          snakeCol[i] = snakeCol[i + 1];
        }
    }
  }
  
}
void updateSnake(){
  // increase the size of the snake with 1 point attached to the tail
  int tailRow2, tailCol2;

  snakeLength ++;
  for(int i = snakeLength-1; i > 0; i--){
    snakeRow[i] = snakeRow[i - 1];
    snakeCol[i] = snakeCol[i - 1];
  }

  tailRow = snakeRow[1];
  tailCol = snakeCol[1];
  tailRow2 = snakeRow[2];
  tailCol2 = snakeCol[2];

  if(tailRow2 == tailRow){
    if(tailCol < tailCol2){
      // right
      snakeRow[0] = tailRow;
      snakeCol[0] = min(0, tailCol - 1);
    }else{
      // left
      snakeRow[0] = tailRow;
      snakeCol[0] = max(7, tailCol + 1);
    }
  }else if(tailCol2 == tailCol){
    if(tailRow < tailRow2){
      // under
      snakeRow[0] = min(0, tailRow - 1);
      snakeCol[0] = tailCol;
    }else{
      // above
      snakeRow[0] = max(7, tailRow + 1);
      snakeCol[0] = tailCol;
    }
  }
}
void increaseGameSpeed(){
  if(level == 10 || level == 6 || level == 3){
    moveGameInterval = moveGameInterval - 20;
  }
}
void eatFood(){
   headRow = snakeRow[snakeLength - 1];
   headCol = snakeCol[snakeLength - 1];
   
   if(headRow == foodRow && headCol == foodCol){
        eatSound();
        if(difficultyLevel == 3){
          points += 5;
        }else if(difficultyLevel == 2){
          points += 2;
        }else{
          points ++; 
        }
        level ++;
        increaseGameSpeed();
        updateGame(level, points);//update LCD with score
        // generate new food && new snake
        updateSnake();
        showSnake();
        generateFood();
        showFood(true);
   }
}

bool dead(){
  headRow = snakeRow[snakeLength - 1];
  headCol = snakeCol[snakeLength - 1];

  // suicide
  for(int i = 0; i < snakeLength - 1; i++){
    if(snakeCol[i] == headCol && snakeRow[i] == headRow){
      return true;
    }
  }
  
  // hit the obstacle
  for(int i = 0; i< numberOfWalls; i++){
    if(wallsRow[i] == headRow && wallsCol[i] == headCol){
      return true;
    }
  }
  return false;
}
void gameOver(){
  playAgainScreen = true;
  if(points > EEPROM.read(5)){
    congratsHighScore(points);
    congratsHighScoreScreen = true;
    enteringPlayerName = true;
    congratsHighScore(points);
  }else{
    congratsScreen = true;
    congrats(points);
  }
}
void moveGame(int nextPosition, bool directionRow){
  eatFood();
  moveTheSnake(nextPosition, directionRow);
  if(dead()){
      colisionSound();
      gameOver();
  }
}
void updateSnakePosition(){
  if(joystickMovedUp()){
    moveGame(snakeRow[snakeLength - 1] + 1, true);
  }else if(joystickMovedDown()){
    moveGame(snakeRow[snakeLength - 1] - 1, true);
  }else if(joystickMovedRight()){
    moveGame(snakeCol[snakeLength - 1] - 1, false);
  }else if(joystickMovedLeft()){
    moveGame(snakeCol[snakeLength - 1] + 1, false);
  }
}
