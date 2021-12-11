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
    if(joystickMovedRight() && difficultyLevel < maxInterval){
        difficultyLevel ++;
        difficultyMenu();
    }else if(joystickMovedLeft() && difficultyLevel > minInterval){
        difficultyLevel --;
        difficultyMenu();
    }
    break;
  case 1:
    if(joystickMovedRight() || joystickMovedLeft()){
        mute = !mute;
        changeSound();
    }
    break;
  case 2:
    if(joystickMovedRight() && contrastLevel < maxInterval){
        contrastLevel ++;
        changeContrast();
    }else if(joystickMovedLeft() && contrastLevel > minInterval){
        contrastLevel --;
        changeContrast();
    }
    break;
  case 3:
    if(joystickMovedRight() && brightnessLevel < maxInterval){
        brightnessLevel ++;
        changeBrightness();
    }else if(joystickMovedLeft() && brightnessLevel > minInterval){
        brightnessLevel --;
        changeBrightness();
    }
    break;
  case 4:
    if(joystickMovedRight() && matrixIntensityLevel < maxInterval){
        matrixIntensityLevel ++;
        matrixIntensityMenu();
    }else if(joystickMovedLeft() && matrixIntensityLevel > minInterval){
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
      if(joystickPressed()){
        settingsMenu();
      }
    }else if(joystickMovedDown()){
        currentSettingsMenu ++;
        if(currentSettingsMenu > 5){
          currentSettingsMenu = 0;
        }
        settingsMenu();
    }else if(joystickMovedUp()){
        currentSettingsMenu --;
        if(currentSettingsMenu < 0){
          currentSettingsMenu = 5;
        }
        settingsMenu();
    }else if(joystickMovedRight() && settingsMenuOpened){
      changeSubSettingsMenu();
    }else if(joystickMovedLeft() && subSettingsMenuOpened){
        settingsMenu();
    }
}
