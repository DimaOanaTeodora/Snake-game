// Game objects - snake, obstacles, food
// Variables
String difficulty[] ={"LOW", "MEDIUM", "HIGH"};
byte difficultyLevel = 1;
/* LOW: no obstacles, 1 point/level 
 * MEDIUM: 2 tiny obstacles, 5 points/level
 * HIGH: 4 walls on the corners, 10 points/level
 * ++ increase the spead 
 */
// GAME 
int level = 1;
int points = 0;

// SNAKE
int snakeLength = 3;
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
  // HIGH difficulty
  wallsRow[numberOfWalls] = 0;
  wallsRow[numberOfWalls + 1] = 7;
  wallsRow[numberOfWalls + 2] = 7;
  wallsRow[numberOfWalls + 3] = 0;
  
  wallsCol[numberOfWalls] = 0;
  wallsCol[numberOfWalls + 1] = 7;
  wallsCol[numberOfWalls + 2] = 0;
  wallsCol[numberOfWalls + 3] = 7;
  numberOfWalls = 4;
  
  for(int i=1; i<=2; i++){
    wallsRow[numberOfWalls] = 0;
    wallsRow[numberOfWalls + 1] = i;
    wallsRow[numberOfWalls + 2] = 7 - i;
    wallsRow[numberOfWalls + 3] = 0;
    wallsRow[numberOfWalls + 4] = 7 - i;
    wallsRow[numberOfWalls + 5] = 7;
    wallsRow[numberOfWalls + 6] = 7;
    wallsRow[numberOfWalls + 7] = i;
    
    wallsCol[numberOfWalls] = i;
    wallsCol[numberOfWalls + 1] = 0;
    wallsCol[numberOfWalls + 2] = 0;
    wallsCol[numberOfWalls + 3] = 7 - i;
    wallsCol[numberOfWalls + 4] = 7;
    wallsCol[numberOfWalls + 5] = 7 - i;
    wallsCol[numberOfWalls + 6] = i;
    wallsCol[numberOfWalls + 7] = 7;
    numberOfWalls += 8;
  }
}
void tinyObstacles(){
  // MEDIUM difficulty
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
  
  snakeLength = 3;
  snakeRow[0] = row;
  snakeCol[0] = col;
  snakeRow[1] = row;
  snakeCol[1] = col + 1;
  snakeRow[2] = row;
  snakeCol[2] = col + 2;
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
