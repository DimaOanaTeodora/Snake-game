//START - TODO
void start() {
   
  updateMatrixDisplay(three); 
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("GAME");

  delay(1500);

  updateMatrixDisplay(two);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("SET");

  delay(1500);

  updateMatrixDisplay(one);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("GO!");

  delay(1500);
}

//HIGH SCORE - TODO
void highScore(){
  String playerName = "Ana";
  int highScore = 20; 
  
  //TODO: Memory.returnHighScore(highScore, playerName);
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print(playerName);
  lcd.print(": ");
  lcd.print(highScore);
  
  lcd.setCursor(10, 1);
  lcd.print("<<back");
}

//SETTINGS

// ABOUT
void about(){
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Credits");
  lcd.setCursor(1, 1);
  lcd.print("Oana Dima 341");

  delay(1500);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Introduction");
  lcd.setCursor(3, 1);
  lcd.print("to Robotics");
  
  delay(1500);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("github.com/");
  lcd.setCursor(0, 1);
  lcd.print("DimaOanaTeodora");

  delay(1500);
  
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Thanks!");
  lcd.setCursor(5, 1);
  lcd.print("<<back");
}
