#include <LiquidCrystal.h>
//Variables
const int RS = 13;
const int enable = 8;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const byte contrastPin = 6;
const byte brightnessPin = 9;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

int contrastValue= 105;
int brightnessValue = 28836;
byte brightnessLevel = 2;
byte contrastLevel = 1;
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
void greetings() {
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("~SNAKE~");
  
  lcd.setCursor(6, 1);
  lcd.print("Hi!");

  updateMatrixDisplay(hi);
  delay(1500);
}
void congrats(int points) {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Congrats!");
  
  lcd.setCursor(1, 1);
  lcd.print("Your score: ");
  lcd.print(points);

  //updateMatrixDisplay(hi); - TODO
  delay(2500);
}
void congratsHighScore(int points) {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("New high score");
  
  lcd.setCursor(4, 1);
  lcd.print(points);
  lcd.print(" points");
 
  // heart updateMatrixDisplay(hi); - TODO
  delay(2500);
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
  lcd.print(EEPROM.read(0));
}
void updateGame(int level, int points){
  lcd.setCursor(6, 0);
  lcd.print(level);
  
  lcd.setCursor(6, 1);
  lcd.print(points);
}
