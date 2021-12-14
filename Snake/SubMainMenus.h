//START 
void start() {
  menuSound();
  updateMatrixDisplay(three); 
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("GAME");

  delay(delayMainMenus);

  menuSound();
  updateMatrixDisplay(two);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("SET");

  delay(delayMainMenus);

  menuSound();
  updateMatrixDisplay(one);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("GO!");

  delay(delayMainMenus);

  gameHasStarted = true;
}
//HIGH SCORE 
void highScore(){
  String playerName;
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("LEADERBOARD");
  lcd.setCursor(2, 1);
  lcd.print("1.");
  playerName = readStringFromEEPROM(8);
  for(int i = 0; i < 4; i++){
    if(playerName[i] == '_'){
       playerName[i]=' ';
    }
  }
  lcd.print(playerName);
  lcd.print(" ");
  lcd.print(EEPROM.read(5));

  delay(delayMainMenus);
   
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("LEADERBOARD");
  lcd.setCursor(2, 1);
  lcd.print("2.");
  playerName = readStringFromEEPROM(9);
  for(int i = 0; i < 4; i++){
    if(playerName[i] == '_'){
       playerName[i]=' ';
    }
  }
  lcd.print(playerName);
  lcd.print(" ");
  lcd.print(EEPROM.read(6));

  delay(delayMainMenus);
   
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("LEADERBOARD");
  lcd.setCursor(2, 1);
  lcd.print("3.");
  playerName = readStringFromEEPROM(10);
  for(int i = 0; i < 4; i++){
    if(playerName[i] == '_'){
       playerName[i]=' ';
    }
  }
  lcd.print(playerName);
  lcd.print(" ");
  lcd.print(EEPROM.read(7));

  delay(delayMainMenus);

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

  delay(delayMainMenus);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Introduction");
  lcd.setCursor(3, 1);
  lcd.print("to Robotics");
  
  delay(delayMainMenus);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("github.com/");
  lcd.setCursor(0, 1);
  lcd.print("DimaOanaTeodora");

  delay(delayMainMenus);
  
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Thanks!");
  lcd.setCursor(5, 1);
  lcd.print("<<back");
}
