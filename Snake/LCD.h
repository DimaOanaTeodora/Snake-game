#include <LiquidCrystal.h>
//Variables
const int RS = 12; 
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const byte contrastPin = 6;
const byte brightnessPin = 9;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

int contrastValue= 70;
int brightnessValue = 28836;
byte brightnessLevel = 2;
byte contrastLevel = 2;
byte minInterval = 1;
byte maxInterval = 3;

//Functions
void enterPlayerName(){
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Name: ");
  lcd.print("____");
  lcd.setCursor(1, 1);
  lcd.print("Press to save!");
}
void updatePlayerName(String playerName){
  lcd.setCursor(9, 0);
  lcd.print(playerName);
}
void greetings(){
  menuSound();
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("~SNAKE~");
  lcd.setCursor(6, 1);
  lcd.print("Hi!");

  updateMatrixDisplay(hi);
  delay(1500);
}
void congrats(int points) {
  updateMatrixDisplay(fullHeart);
  
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Congrats!");
  lcd.setCursor(1, 1);
  lcd.print("Your score: ");
  lcd.print(points);

  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Move to continue");
  lcd.setCursor(1, 1);
  lcd.print("Your score: ");
  lcd.print(points);
}
void congratsHighScore(int points) {
  updateMatrixDisplay(fullHeart);
  
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("New HighS: ");
  lcd.print(points);
  lcd.setCursor(0, 1);
  lcd.print("Move to continue");
}
void playAgain(){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Play again?");
  lcd.setCursor(0, 1);
  lcd.print("Y-move");
  lcd.setCursor(9, 1);
  lcd.print("N-press");

  updateMatrixDisplay(questionMark);
}
void game(){
  // LCD during the game
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level ");
  lcd.print(1);
  lcd.setCursor(0, 1);
  lcd.print("SCORE ");
  lcd.print(0);
  lcd.setCursor(10, 0);
  lcd.print("High ");
  lcd.setCursor(10, 1);
  lcd.print(EEPROM.read(5));
}
void updateGame(int level, int points){
  // update LCD with level and current score during the game
  lcd.setCursor(6, 0);
  lcd.print(level);
  lcd.setCursor(6, 1);
  lcd.print(points);
}
