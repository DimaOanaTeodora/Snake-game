#include<LiquidCrystal.h>
#include<EEPROM.h>
//#include "Memory.h"
/*
 * TODO:
 * enter player name si dupa intra in joc
 * salvare in memorie stringuri
 * submeniurile de setari din settings
 * sectiunea about
 * headere la final
 * save the name to eeprom
 * buguri la nume
 * bug scroll down settings menu
*/
//LCD
const int RS = 9;
const int enable = 8;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

// Joystick - Switch
const int joyX = A0;
const int joyY = A1;
const int pinSw = 7;
const int minTreshold = 350;
const int maxTreshold = 550;
int xValue = 0;
int yValue = 0;
bool switchState = LOW; //Joystick button
bool joyMoved = false;
bool joyMovedUp = false;
bool joyMovedDown = false;
bool joyMovedLeft = false;
bool joyMovedRight = false;

//Game variables
bool gameHasStarted = false;
int memoryIndexCounter = 0;

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
void setup(){
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  
  pinMode(RS, OUTPUT);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(pinSw, INPUT_PULLUP);
  
  greetings();
  scrollMainMenu("START");
  
  Serial.begin(9600);
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

void enterPlayerNameSubMenu(){
  enteringPlayerName = true;
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("NAME: ");

  enterPlayerName();
    
  lcd.setCursor(0, 1);
  lcd.print("Press to START");
}
void enterPlayerName(){
  lcd.setCursor(6,0);
  lcd.print(playerName);
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

void verifyIfJoystickWasMoved(){
   if(joyMoved == true){
    if(xValue > minTreshold && xValue < maxTreshold){
      joyMoved = false;
     }else if(yValue > minTreshold && yValue < maxTreshold){
      joyMoved = false;
     }
   }
   if(joyMoved == false){
     if(xValue < minTreshold || yValue < minTreshold){
      joyMoved = true;
     }else if(xValue > maxTreshold || yValue > maxTreshold){
      joyMoved = true;
     }
   }
}
void verifyIfJoystickWasMovedUp(){
  if(yValue >= minTreshold){
    joyMovedUp = false;
  }else if(yValue < minTreshold){
    joyMovedUp = true;
  }
}
void verifyIfJoystickWasMovedDown(){
  if(yValue <= maxTreshold){
    joyMovedDown = false;
  }else if(yValue > maxTreshold){
    joyMovedDown = true;
  }
}
void verifyIfJoystickWasMovedRight(){
  if(xValue <= maxTreshold){
    joyMovedRight = false;
  }else if(xValue > maxTreshold){
    joyMovedRight = true;
  }
}
void verifyIfJoystickWasMovedLeft(){
  if(xValue >= minTreshold){
    joyMovedLeft = false;
  }else if(xValue < minTreshold){
    joyMovedLeft = true;
  }
}
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
void loop(){
  /*read switch state
  cand e apasat sa faca enteringPlayerName = false*/
   xValue = analogRead(joyX);
   yValue = analogRead(joyY);
   switchState = digitalRead(pinSw);

   Serial.println(switchState);

   if(switchState == LOW && enteringPlayerName == true){
      gameLCD(1,1);
      enteringPlayerName = false;
      savePlayerName();
   }

   verifyIfJoystickWasMoved();
   verifyIfJoystickWasMovedUp();
   verifyIfJoystickWasMovedDown();
   verifyIfJoystickWasMovedRight();
   verifyIfJoystickWasMovedLeft();

   if (joyMovedUp == true){
    if(enteringPlayerName == true){
         alphabetPosition +=1;
         if(alphabetPosition >= alphabet.length()){
            alphabetPosition = 0;
         }
         playerName[playerNamePosition]= alphabet[alphabetPosition];
         enterPlayerNameSubMenu();
    }else if(mainMenuOpened == true){
      mainMenuOption --;
      if(mainMenuOption == -1){
        mainMenuOption = 3;
      }else if(mainMenuOption == 4){
        mainMenuOption = 0;
      }
      scrollMainMenu(mainMenuOptions[mainMenuOption]);
    }else if(settingsMenuOpened == true){
      settingsMenuOption --;
      if(settingsMenuOption == -1){
        settingsMenuOption = 5;
      }else if(mainMenuOption == 6){
        settingsMenuOption = 0;
      }
      scrollSettingsMenu(settingsMenuOptions[settingsMenuOption]);
    }
    delay(250);
   }
   
   if(joyMovedDown == true){
    if(enteringPlayerName == true){
         alphabetPosition -=1;
         if(alphabetPosition <= 0){
            alphabetPosition = alphabet.length()-1;
         }
         playerName[playerNamePosition]= alphabet[alphabetPosition];
         enterPlayerNameSubMenu();
    }else if(mainMenuOpened == true){
      mainMenuOption ++;
      if(mainMenuOption == -1){
        mainMenuOption = 3;
      }else if(mainMenuOption == 4){
        mainMenuOption = 0;
      }
      scrollMainMenu(mainMenuOptions[mainMenuOption]);
    }else if(settingsMenuOpened == true){
      settingsMenuOption ++;
      if(settingsMenuOption == -1){
        settingsMenuOption = 5;
      }else if(mainMenuOption == 6){
        settingsMenuOption = 0;
      }
      scrollSettingsMenu(settingsMenuOptions[settingsMenuOption]);
    }
    delay(250);
   }

   if (joyMovedRight == true){
    if(enteringPlayerName == true){
        playerNamePosition +=1;
        if(playerNamePosition >= 10){
          playerNamePosition = 0;
        }
        alphabetPosition = -1;
        enterPlayerNameSubMenu();      
    }else if(mainMenuOpened == true){
      if(mainMenuOption == 0){
        //gameLCD(1,1);
        enterPlayerNameSubMenu();
        gameHasStarted = true;
      }else if(mainMenuOption == 1){
          highScoreMenu();
      }else if(mainMenuOption == 2){
          toSettingsMenu();
      }else if(mainMenuOption == 3){
        aboutMenu();
      }
    }else if(settingsMenuOpened == true){
      if(settingsMenuOption == 0){
          //gameLCD(1,1);
          //gameHasStarted = true;
        }else if(settingsMenuOption == 1){
            //highScoreMenu();
        }else if(settingsMenuOption == 2){
            //toSettingsMenu()
        }else if(settingsMenuOption == 3){
          //aboutMenu();
        }else if(settingsMenuOption == 4){
          //aboutMenu();
        }else if(settingsMenuOption == 5){
          backFromSettingsMenu();
        }
    }
    delay(250);
   }

   if (joyMovedLeft == true){
    if(enteringPlayerName == true){
        playerNamePosition -=1;
        if(playerNamePosition <= 0){
          playerNamePosition = 9;
        }
        enterPlayerNameSubMenu();      
    }else if(mainMenuOpened == true && subMenuOpened == true){
      backFromSubMainMenus();
    }else if(settingsMenuOpened == true && subMenuOpened == true){
      backFromSubSettingsMenus();
    }
    delay(250);
   }
}
