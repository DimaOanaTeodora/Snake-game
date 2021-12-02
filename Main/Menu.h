#include"LCD.h"
//Menu variables
String mainMenuOptions[]={"START", "HIGH SCORE", "SETTINGS", "ABOUT"};
int mainMenuOption = 0; // max 3
String settingsMenuOptions []={"DIFICULTY", "MUTE", "LCD CONTRAST", "LCD BRIGHT", "MATRIX BRIGHT", "BACK"}; 
int settingsMenuOption = 0;
bool mainMenuOpened = false; // max 5
bool settingsMenuOpened = false;
bool subMenuOpened = false;
bool enteringPlayerName = false;
String playerName = "__________"; // max 10 
String alphabet = "abcdefghijklmnopqrstuvwxyz";
int playerNamePosition = 0;
int alphabetPosition = -1;
void scrollMenu(String option){
 
  if(option.length() <=7){
    lcd.setCursor(4, 1);
  }else{
    lcd.setCursor(2, 1);
  }
  lcd.print(">");
  lcd.print(option);
}
void scrollMainMenu(String option){
  mainMenuOpened = true;
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Move to scroll");
  scrollMenu(option);
}
void scrollSettingsMenu(String option){
  settingsMenuOpened = true;
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Settings");
  scrollMenu(option);
}

void greetings() {
  /*
  Set LCD screen greetings message:
      ~SNAKE~
        Hi!
  */
  lcd.clear();
  
  lcd.setCursor(4, 0);
  lcd.print("~SNAKE~");
  
  lcd.setCursor(6, 1);
  lcd.print("Hi!");

  delay(2000);
}
void gameLCD(int currentLevel, int currentScore) { 
   /*
  Set LCD screen during a game:
      LEVEL x   Best
      Score y   zzz
  */
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("LEVEL ");
  lcd.print(currentLevel);
  
  lcd.setCursor(0, 1);
  lcd.print("Score ");
  lcd.print(currentScore);
  
  lcd.setCursor(10, 0);
  lcd.print("Best");
  
  lcd.setCursor(10, 1);
  //lcd.print(returnHighScore());
  lcd.print(20);
}
void highScoreMenu(){
  /*
   * playerName: highScore
   *                        <<back
   */
  subMenuOpened = true;
  
  String playerName = "Ana";
  int highScore = 20; 
  
  //Memory.returnHighScore(highScore, playerName);
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print(playerName);
  lcd.print(": ");
  lcd.print(highScore);
  
  lcd.setCursor(10, 1);
  lcd.print("<<back");
}
void aboutMenu(){
  /*
   * changing menu
   */
  subMenuOpened = true;
  
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Credits");
  lcd.setCursor(1, 1);
  lcd.print("Oana Dima 341");

  delay(2000);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Introduction");
  lcd.setCursor(3, 1);
  lcd.print("to Robotics");
  
  delay(2000);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("github.com/");
  lcd.setCursor(0, 1);
  lcd.print("DimaOanaTeodora");

  delay(2000);
  
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Thanks!");
  lcd.setCursor(5, 1);
  lcd.print("<<back");
}
void enterPlayerName(){
  lcd.setCursor(6,0);
  lcd.print(playerName);
}
void enterPlayerNameSubMenu(){
  enteringPlayerName = true;
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("NAME: ");

  enterPlayerName();
    
  lcd.setCursor(0, 1);
  lcd.print("Press to START");
}
void backFromSubMainMenus(){
  subMenuOpened = false;
  scrollMainMenu(mainMenuOptions[mainMenuOption]);
}
void backFromSubSettingsMenus(){
  subMenuOpened = false;
  scrollSettingsMenu(settingsMenuOptions[settingsMenuOption]);
}

void backFromSettingsMenu(){
  mainMenuOption = 0;
  mainMenuOpened = true;
  settingsMenuOpened = false;
  scrollMainMenu(mainMenuOptions[mainMenuOption]);
}
void toSettingsMenu(){
  settingsMenuOption = 0;
  mainMenuOpened = false;
  settingsMenuOpened = true;
  scrollSettingsMenu(settingsMenuOptions[settingsMenuOption]);
}
/*
   Move to scroll
   START -> ENTER NAME
   HIGH SCORE
   SETTINGS
    (X) ENTER NAME
    DIFICULTY 
    LCD CONTRAST
    LCD BRIGHTNESS
    MATRIX BRIGHTNESS
    CHOOSE THEME SONG (*)
   ABOUT
      SCROLLING TEXT (*)
  */

void savePlayerName(){
    String copy = playerName;
    playerName = "";
    for (int i = 0; i< copy.length(); i++){
      if(copy[i] == '_'){
        break;
      }else{
        playerName.concat(copy[i]);
      }
    }
    //save to EEPROM 
    Serial.println(playerName);
}
