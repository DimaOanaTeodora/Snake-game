//START 
void start() {
  menuSound();
  updateMatrixDisplay(three); 
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("GAME");

  delay(1500);

  menuSound();
  updateMatrixDisplay(two);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("SET");

  delay(1500);

  menuSound();
  updateMatrixDisplay(one);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("GO!");

  delay(1500);

  gameHasStarted = true;
}
//HIGH SCORE 
void highScore(){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("LEADERBOARD");
  lcd.setCursor(2, 1);
  lcd.print("1.");
  lcd.print(readStringFromEEPROM(8));
  lcd.print(" ");
  lcd.print(EEPROM.read(5));

  delay(1500);
   
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("LEADERBOARD");
  lcd.setCursor(2, 1);
  lcd.print("2.");
  lcd.print(readStringFromEEPROM(9));
  lcd.print(" ");
  lcd.print(EEPROM.read(6));

  delay(1500);
   
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("LEADERBOARD");
  lcd.setCursor(2, 1);
  lcd.print("3.");
  lcd.print(readStringFromEEPROM(10));
  lcd.print(" ");
  lcd.print(EEPROM.read(7));

  delay(1500);

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("<<back");
}
// ABOUT
void about(){
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("SNAKE~~Credits");
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
