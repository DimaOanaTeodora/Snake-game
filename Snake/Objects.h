/* Game objects: snake, obstacles, food
   Difficulty:
    LOW: no obstacles, 1 point/level
    MEDIUM: 2 tiny obstacles, 2 points/level
    HIGH: 4 walls on the corners, 5 points/level
    ++ increase the speed
*/
String const difficulty[] = {"LOW", "MEDIUM", "HIGH"};
byte difficultyLevel = 1;

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

void cornerWalls() {
  // HIGH difficulty
  // fixed walls during the entire game sesion
  // just increasing the speed
  lc.clearDisplay(0);
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
void tinyObstacles() {
  // MEDIUM difficulty
  // fixed random walls during the entire game sesion
  // just increasing the speed
  lc.clearDisplay(0);
  int row = random(0, matrixSize - 1);
  int col = random(0, matrixSize - 1);

  wallsRow[0] = row;
  wallsCol[0] = col;
  wallsRow[1] = row;
  wallsCol[1] = col + 1;

  row = random(0, matrixSize - 1);
  col = random(0, matrixSize - 1);

  wallsRow[2] = row;
  wallsCol[2] = col;
  wallsRow[3] = row + 1;
  wallsCol[3] = col;
  numberOfWalls = 4;
}
bool isPartOfObstacle(int row, int col) {
  // true if a point(row, col) is part of a wall
  for (int i = 0; i < numberOfWalls; i++) {
    if (wallsRow[i] == row && wallsCol[i] == col) {
      return true;
    }
  }
  return false;
}
void generateSnake() {
  // random generating the head of the snake
  int row, col, maxInterval, minInterval;

  if (difficultyLevel == 3) {
    maxInterval = matrixSize - 3;
    minInterval = matrixSize - 2;
  } else {
    maxInterval = matrixSize - 2;
    minInterval = matrixSize;
  }

  do {
    row = random(0, minInterval);
    col = random(0, maxInterval);
  } while (isPartOfObstacle(row, col));

  snakeRow[0] = row;
  snakeCol[0] = col;
  snakeRow[1] = row;
  snakeCol[1] = col + 1;
  snakeLength = 2;
}
bool isPartOfSnake(int row, int col) {
  // true if a point(row, col) is part of the snake
  for (int i = 0; i < snakeLength; i++) {
    if (snakeRow[i] == row && snakeCol[i] == col) {
      return true;
    }
  }
  return false;
}
void generateFood() {
  // generate random the food
  int row, col;

  do {
    row = random(0, matrixSize);
    col = random(0, matrixSize);
  } while (isPartOfSnake(row, col) || isPartOfObstacle(row, col));

  lastFoodRow = foodRow;
  lastFoodCol = foodCol;
  foodRow = row;
  foodCol = col;
}
