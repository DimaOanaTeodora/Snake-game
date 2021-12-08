//Variables
int currentMainMenu = 0; // [0,3]

String mainMenuOptions[]={"START", "HIGH SCORE", "SETTINGS", "ABOUT"};

bool mainMenuOpened = false;
bool subMainMenuOpened = false;

// Functions
void mainMenu(){
  subMainMenuOpened = false;
  mainMenuOpened = true;
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Move to scroll");
  
  if(mainMenuOptions[currentMainMenu].length()>6){
    lcd.setCursor(2,1);
  }else{
    lcd.setCursor(4,1);
  }
  lcd.print(">>");
  lcd.print(mainMenuOptions[currentMainMenu]);
}
void changeSubMainMenu(){
  subMainMenuOpened = true;
  switch (currentMainMenu) {
  case 0:
    start();
    game();
    resetGame();
    break;
  case 1:
    highScore();
    break;
  case 2:
    mainMenuOpened = false;
    subMainMenuOpened = false;
    settingsMenu();
    break;
  case 3:
    about();
    break;
  }
}
void updateMainMenu(){
   if(joystickMovedDown()){
        currentMainMenu ++;
        if(currentMainMenu > 3){
          currentMainMenu = 0;
        }
        mainMenu();
    }else if(joystickMovedUp()){
        currentMainMenu --;
        if(currentMainMenu < 0){
          currentMainMenu = 3;
        }
        mainMenu();
    }else if(joystickMovedRight() && mainMenuOpened){
      changeSubMainMenu();
    }else if(joystickMovedLeft() && subMainMenuOpened){
      mainMenu();
    }
}
