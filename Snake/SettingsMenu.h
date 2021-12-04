//Variables
int currentSettingsMenu = 0; // [0,5] 

String settingsMenuOptions []={"DIFFICULTY", "SOUND", "LCD CONTRAST", "LCD BRIGHT", "MATRIX BRIGHT", "BACK"};

bool settingsMenuOpened = false;
bool subSettingsMenuOpened = false;

// Functions
void settingsMenu(){
  subSettingsMenuOpened = false;
  settingsMenuOpened = true;
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Settings");
  
  if(settingsMenuOptions[currentSettingsMenu].length() > 10){
    lcd.setCursor(1,1);
  }else if(settingsMenuOptions[currentSettingsMenu].length() > 6){
    lcd.setCursor(2,1);
  }else{
    lcd.setCursor(4,1);
  }
  lcd.print(">>");
  lcd.print(settingsMenuOptions[currentSettingsMenu]);
}
void changeSubSettingsMenu(){
  subSettingsMenuOpened = true;
  switch (currentSettingsMenu) {
  case 0:
    difficultyMenu();
    break;
  case 1:
    soundMenu();
    changeSound();
    break;
  case 2:
    contrastMenu();
    changeContrast();
    break;
  case 3:
    brightnessMenu();
    changeBrightness();
    break;
  case 4:
    matrixIntensityMenu();
    break;
  }
}
void changeValuesSubSettingsMenu(){
  switch (currentSettingsMenu) {
  case 0:
    if(ifJoystickMovedRight() && difficultyLevel < maxInterval){
        difficultyLevel ++;
        difficultyMenu();
    }else if(ifJoystickMovedLeft() && difficultyLevel > minInterval){
        difficultyLevel --;
        difficultyMenu();
    }
    break;
  case 1:
    if(ifJoystickMovedRight() && soundLevel < maxInterval){
        soundLevel ++;
        changeSound();
    }else if(ifJoystickMovedLeft() && soundLevel > minInterval){
        soundLevel --;
        changeSound();
    }
    break;
  case 2:
    if(ifJoystickMovedRight() && contrastLevel < maxInterval){
        contrastLevel ++;
        changeContrast();
    }else if(ifJoystickMovedLeft() && contrastLevel > minInterval){
        contrastLevel --;
        changeContrast();
    }
    break;
  case 3:
    if(ifJoystickMovedRight() && brightnessLevel < maxInterval){
        brightnessLevel ++;
        changeBrightness();
    }else if(ifJoystickMovedLeft() && brightnessLevel > minInterval){
        brightnessLevel --;
        changeBrightness();
    }
    break;
  case 4:
    if(ifJoystickMovedRight() && matrixIntensityLevel < maxInterval){
        matrixIntensityLevel ++;
        matrixIntensityMenu();
    }else if(ifJoystickMovedLeft() && matrixIntensityLevel > minInterval){
        matrixIntensityLevel --;
        matrixIntensityMenu();
    }
    break;
  }
}
// BACK 
void back(){
   settingsMenuOpened = false;
   subSettingsMenuOpened = false;
}

void updateSettingsMenu(){
    if(subSettingsMenuOpened == true){
      changeValuesSubSettingsMenu();
      if(ifJoystickPressed()){
        settingsMenu();
      }
    }else if(ifJoystickMovedDown()){
        currentSettingsMenu ++;
        if(currentSettingsMenu > 5){
          currentSettingsMenu = 0;
        }
        settingsMenu();
    }else if(ifJoystickMovedUp()){
        currentSettingsMenu --;
        if(currentSettingsMenu < 0){
          currentSettingsMenu = 5;
        }
        settingsMenu();
    }else if(ifJoystickMovedRight() && settingsMenuOpened){
      changeSubSettingsMenu();
    }else if(ifJoystickMovedLeft() && subSettingsMenuOpened){
        settingsMenu();
    }
}
