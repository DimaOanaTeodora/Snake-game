// Game objects - snake, obstacles, food
// Variables
String difficulty[] ={"LOW", "MEDIUM", "HIGH"};
byte difficultyLevel = 1;
/* LOW: no obstacles, 1 point/level 
 * MEDIUM: 2 tiny obstacles, 2 points/level
 * HIGH: 4 walls on the corners, 5 points/level
 * ++ increase the spead 
 */
// GAME 
int level = 1;
int points = 0;

// SNAKE
int snakeLength = 2;
int snakeRow[32];
int snakeCol[32];
int tailRow = -1;
int tailCol = -1;
int headRow = -1;
int headCol = -1;
int bodyRow = -1;
int bodyCol = -1;

// OBSTACLES
int numberOfWalls = 0;
int wallsRow[20];
int wallsCol[20];

// FOOD
int foodRow = -1;
int foodCol = -1;
int lastFoodRow = -1;
int lastFoodCol = -1;

// PLAYER
String player = "____";
String alphabet = "abcdefghijklmnopqrstuvwxyz";
byte alphabetLength = alphabet.length();
int currentLetterPosition = -1;
int currentPlayerNamePosition = 0;
bool enteringPlayerName = false;
bool playAgainScreen = false;

//Functions
unsigned int newRandom(unsigned int minimum, unsigned int maximum){
  // Arduino bug: the random(x,y) function doesn't work properly
  return minimum + random() % (maximum - minimum);
}
void cornerWalls(){
  lc.clearDisplay(0);
  // HIGH difficulty
  wallsRow[0] = 0;
  wallsCol[0] = 0;
  
  wallsRow[1] = 7;
  wallsCol[1] = 7;
  
  wallsRow[2] = 7;
  wallsCol[2] = 0;
  
  wallsRow[3] = 0;
  wallsCol[3] = 7;
  
  wallsRow[4] = 0;
  wallsCol[4] = 1;

  wallsRow[5] = 1;
  wallsCol[5] = 0;

  wallsRow[6] = 0;
  wallsCol[6] = 6;

  wallsRow[7] = 6;
  wallsCol[7] = 0;

  wallsRow[8] = 7;
  wallsCol[8] = 6;

  wallsRow[9] = 6;
  wallsCol[9] = 7;

  wallsRow[10] = 7;
  wallsCol[10] = 1;

  wallsRow[11] = 1;
  wallsCol[11] = 7;
  
  numberOfWalls = 12;
}
void tinyObstacles(){
  // MEDIUM difficulty
  lc.clearDisplay(0);
  int row = newRandom(0, matrixSize - 1);
  int col = newRandom(0, matrixSize - 1);
  
  numberOfWalls = 0;
  wallsRow[numberOfWalls] = row;
  wallsRow[numberOfWalls + 1] = row;
  wallsCol[numberOfWalls] = col;
  wallsCol[numberOfWalls + 1] = col + 1;
  
  row = newRandom(0, matrixSize - 1);
  col = newRandom(0, matrixSize - 1);

  wallsRow[numberOfWalls + 2] = row;
  wallsRow[numberOfWalls + 3] = row + 1;
  wallsCol[numberOfWalls + 2] = col;
  wallsCol[numberOfWalls + 3] = col;
  numberOfWalls = 4;
}
bool isPartOfObstacle(int row, int col){
  // true if a point(row, col) is part of a wall
  for(int i = 0; i< numberOfWalls; i++){
    if(wallsRow[i] == row && wallsCol[i] == col){
      return true;
    }
  }
  return false;
}
void generateSnake(){
  // random generating the head snake
  int row, col, maxInterval, minInterval;
  
  if(difficultyLevel == 3){
    maxInterval = matrixSize - 3;
    minInterval = matrixSize - 2;
  }else{
     maxInterval = matrixSize - 2;
     minInterval = matrixSize;
  }
  
  do{
    row = newRandom(0, minInterval);
    col = newRandom(0, maxInterval);
  }while(isPartOfObstacle(row, col));
  
  snakeLength = 2;
  snakeRow[0] = row;
  snakeCol[0] = col;
  snakeRow[1] = row;
  snakeCol[1] = col + 1;
  //snakeRow[2] = row;
  //snakeCol[2] = col + 2;
}
bool isPartOfSnake(int row, int col){
  // true if a point(row, col) is part of the snake
  for(int i = 0; i < snakeLength; i++){
     if(snakeRow[i] == row && snakeCol[i] == col){
      return true;
     }
  }
  return false;
}
void generateFood(){
  // generate random the food
  int row, col; 
  
  do{ 
    row = newRandom(0, matrixSize);
    col = newRandom(0, matrixSize);
  }while(isPartOfSnake(row, col) || isPartOfObstacle(row, col));
  
  lastFoodRow = foodRow;
  lastFoodCol = foodCol;
  foodRow = row;
  foodCol = col;
}
