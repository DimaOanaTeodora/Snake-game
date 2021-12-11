// Functions
void showWalls(){
  for(int i = 0; i< numberOfWalls; i++){
    lc.setLed(0, wallsRow[i], wallsCol[i], true);
  }
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
