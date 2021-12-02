#include<EEPROM.h>
#include"Joystick.h"
#include"Menu.h"

//Game variables
bool gameHasStarted = false;
int memoryIndexCounter = 0;

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
