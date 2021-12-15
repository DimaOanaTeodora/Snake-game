String const mainMenuOptions[]={"START", "HIGH SCORE", "SETTINGS", "ABOUT"};
int currentMainMenu = 0; // [0,3]
const int maxValueMainMenu = 3;
const int minValueMainMenu = 0;

bool mainMenuOpened = false;
bool subMainMenuOpened = false;

void mainMenu() {
  // LCD 
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
void changeSubMainMenu() {
  // switch submenus on the LCD 
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
void updateMainMenu() {
  // iterate through main menu options 
   if(joystickMovedDown()) {
        currentMainMenu ++;
        if(currentMainMenu > maxValueMainMenu) {
          currentMainMenu = minValueMainMenu;
        }
        mainMenu();
    }else if(joystickMovedUp()) {
        currentMainMenu --;
        if(currentMainMenu < minValueMainMenu) {
          currentMainMenu = maxValueMainMenu;
        }
        mainMenu();
    }else if(joystickMovedRight() && mainMenuOpened) {
        changeSubMainMenu();
    }else if(joystickMovedLeft() && subMainMenuOpened) {
        mainMenu();
    }
}
