// Variables
String difficulty[] ={"LOW", "MEDIUM", "HIGH"};
byte difficultyLevel = 1;

int snakeLength = 3;
int snakeRow[32];
int snakeCol[32];

int tailRow = -1;
int tailCol = -1;

int foodRow = -1;
int foodCol = -1;

int lastFoodRow = -1;
int lastFoodCol = -1;

int headRow = -1;
int headCol = -1;

int bodyRow = -1;
int bodyCol = -1;

int level = 1;
int points = 0;

bool enteringPlayerName = false;
bool playAgainScreen = false;

//Functions
void generateSnake(){
  snakeLength = 3;
  snakeRow[0] = 1;
  snakeRow[1] = 1;
  snakeRow[2] = 1;
  snakeCol[0] = 1;
  snakeCol[1] = 2;
  snakeCol[2] = 3;
}
void showSnake(){
  if(tailRow != -1 && tailCol != -1){
    lc.setLed(0, tailRow, tailCol, false);
  }
  for(int i=0; i< snakeLength; i++){
     lc.setLed(0, snakeRow[i], snakeCol[i], true);
  }
}
void showFood(){
  if(lastFoodRow != -1 && lastFoodCol != -1){
      lc.setLed(0, lastFoodRow, lastFoodCol, false);
  }
  lc.setLed(0, foodRow, foodCol, true);
}
bool isPartOfSnake(int row, int col){
  for(int i = 0; i < snakeLength; i++){
     if(snakeRow[i] == row && snakeCol[i] == col){
      return true;
     }
  }
  return false;
}
void generateFood(){
  int row; 
  int col; 
  
  do{ 
    row = random(0, matrixSize);
    col = random(0, matrixSize);
  }while(isPartOfSnake(row, col));
  
  lastFoodRow = foodRow;
  lastFoodCol = foodCol;
  foodRow = row;
  foodCol = col;
}
void resetGame(){
  lc.clearDisplay(0);
  enteringPlayerName = false;
  level = 1;
  points = 0; 
  game(); //reset LCD
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
void newSnake(){
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
        points ++;
        level ++;
        updateGame(level, points);//update LCD with score
        // generate new food && new snake
        newSnake();
        showSnake();
        generateFood();
        showFood();
   }
}
bool suicide(){
  headRow = snakeRow[snakeLength - 1];
  headCol = snakeCol[snakeLength - 1];

  for(int i = 0; i < snakeLength - 1; i++){
    if(snakeRow[i] == headRow && snakeCol[i] == headCol){
      return true;
    }
  }
  return false;
}
String player = "____";
String alphabet = "abcdefghijklmnopqrstuvwxyz";
byte alphabetLength = 26;
int currentLetterPosition = -1;
int currentPlayerNamePosition = 0;

void gameOver(){
  congrats(points);
  playAgainScreen = true;
  if(points > EEPROM.read(0)){
    congratsHighScore(points);
    enteringPlayerName = true;
    enterPlayerName();
  }else{
    playAgain();
  }
}
void updateSnakePosition(){
  if(ifJoystickMovedUp()){
    // TODO teleportare

    // GAME OVER CONDITIONS
    if(suicide()){
      gameOver();
      //resetGame();
    }else{ 
      moveTheSnake(snakeRow[snakeLength - 1] + 1, true);
      eatFood();
    }
  }else if(ifJoystickMovedDown()){
    if(suicide()){
      gameOver();
      //resetGame();
    }else{
      moveTheSnake(snakeRow[snakeLength - 1] - 1, true);
      eatFood();
    }
  }else if(ifJoystickMovedRight()){
    if(suicide()){
      gameOver();
      //resetGame();
    }else{
      moveTheSnake(snakeCol[snakeLength - 1] - 1, false);
      eatFood();
    }
  }else if(ifJoystickMovedLeft()){
    // the body is to the left of the head
    if(suicide()){
      gameOver();
      //resetGame();
    }else{
      moveTheSnake(snakeCol[snakeLength - 1] + 1, false);
      eatFood();
    }
  }
}
