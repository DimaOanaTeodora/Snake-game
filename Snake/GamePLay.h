// Variables
bool congratsScreen = false;
bool congratsHighScoreScreen = false;

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
        currentLetterPosition++;
        writePlayerName();
     }else if(joystickMovedDown()){
        currentLetterPosition--;
        writePlayerName();
     }else if(joystickMovedRight()){
        currentPlayerNamePosition++;
        writePlayerName();
     }else if(joystickMovedLeft()){
        currentPlayerNamePosition--;
        writePlayerName();
     }else if(joystickPressed()){
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
  game(); //reset LCD

  // generate obstacles depending on the level 
  if(difficultyLevel == 2){
    tinyObstacles();
    showWalls();
  }else if(difficultyLevel == 3){
    cornerWalls();
    showWalls();
  }
  generateSnake();
  generateFood();
  showSnake();
  showFood();
}
void moveTheSnake(int newValue, bool row){
  tailRow = snakeRow[0];
  tailCol = snakeCol[0];
  
  for(int i = 0; i < snakeLength; i++){
      if(i == snakeLength - 1){
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
void updateSnake(){
  for(int i = snakeLength-1; i > 0; i--){
    snakeRow[i + 1] = snakeRow[i];
    snakeCol[i + 1] = snakeCol[i];
  }
  if(headCol == bodyCol && headRow == bodyRow - 1){
      // the body is above the head
     snakeRow[snakeLength] = snakeRow[snakeLength - 1] + 1;
     snakeCol[snakeLength] = snakeCol[snakeLength - 1];
  }else if(headCol == bodyCol && headRow - 1 == bodyRow){
      // the body is under the head
      snakeRow[snakeLength] = snakeRow[snakeLength - 1] - 1;
      snakeCol[snakeLength] = snakeCol[snakeLength - 1];
   }else if(headRow == bodyRow && headCol - 1 == bodyCol){
      // the body is to the right of the head
      snakeRow[snakeLength] = snakeRow[snakeLength - 1];
      snakeCol[snakeLength] = snakeCol[snakeLength - 1] - 1;
    }else if(headRow == bodyRow && headCol == bodyCol - 11){
      // the body is to the left of the head
      snakeRow[snakeLength] = snakeRow[snakeLength - 1];
      snakeCol[snakeLength] = snakeCol[snakeLength - 1] + 1;
    }
    snakeLength ++;
}
void eatFood(){
   headRow = snakeRow[snakeLength - 1];
   headCol = snakeCol[snakeLength - 1];
   
   if(headRow == foodRow && headCol == foodCol){
        if(difficultyLevel == 3){
          points += 10;
        }else if(difficultyLevel == 2){
          points += 5;
        }else{
          points ++; 
        }
        level ++;
        updateGame(level, points);//update LCD with score
        // generate new food && new snake
        updateSnake();
        showSnake();
        generateFood();
        showFood();
   }
}

bool dead(){
  headRow = snakeRow[snakeLength - 1];
  headCol = snakeCol[snakeLength - 1];

  // suicide
  for(int i = 0; i < snakeLength - 1; i++){
    if(snakeRow[i] == headRow && snakeCol[i] == headCol){
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
  //congrats(points);
  playAgainScreen = true;
  if(points > EEPROM.read(0)){
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
  if(dead()){
      gameOver();
    }else{ 
      moveTheSnake(nextPosition, directionRow);
      eatFood();
   }
}
void updateSnakePosition(){
  if(joystickMovedUp()){
    // TODO teleportare
    moveGame(snakeRow[snakeLength - 1] + 1, true);
  }else if(joystickMovedDown()){
    moveGame(snakeRow[snakeLength - 1] - 1, true);
  }else if(joystickMovedRight()){
    moveGame(snakeCol[snakeLength - 1] - 1, false);
  }else if(joystickMovedLeft()){
    moveGame(snakeCol[snakeLength - 1] + 1, false);
  }
}
