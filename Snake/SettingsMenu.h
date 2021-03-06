String const settingsMenuOptions [] = {"DIFFICULTY", "SOUND", "LCD CONTRAST", "LCD BRIGHT", "MATRIX BRIGHT", "BACK"};
int currentSettingsMenu = 0; // [0,5]
const int maxValueSettingsMenu = 5;
const int minValueSettingsMenu = 0;
const int minInterval = 1;
const int maxInterval = 3;

bool settingsMenuOpened = false;
bool subSettingsMenuOpened = false;

void settingsMenu() {
  // LCD screen
  subSettingsMenuOpened = false;
  settingsMenuOpened = true;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Settings");

  if (settingsMenuOptions[currentSettingsMenu].length() > 10) {
    lcd.setCursor(1, 1);
  } else if (settingsMenuOptions[currentSettingsMenu].length() > 6) {
    lcd.setCursor(2, 1);
  } else {
    lcd.setCursor(4, 1);
  }
  lcd.print(">>");
  lcd.print(settingsMenuOptions[currentSettingsMenu]);
}
void changeSubSettingsMenu() {
  // switch submenus on the LCD
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
void changeValuesSubSettingsMenu() {
  // change the option value(levels) in a submenu of the settings menu
  switch (currentSettingsMenu) {
    case 0:
      if (joystickMovedRight() && difficultyLevel < maxInterval) {
        difficultyLevel ++;
        difficultyMenu();
      } else if (joystickMovedLeft() && difficultyLevel > minInterval) {
        difficultyLevel --;
        difficultyMenu();
      }
      break;
    case 1:
      if (joystickMovedRight() || joystickMovedLeft()) {
        mute = !mute;
        changeSound();
      }
      break;
    case 2:
      if (joystickMovedRight() && contrastLevel < maxInterval) {
        contrastLevel ++;
        changeContrast();
      } else if (joystickMovedLeft() && contrastLevel > minInterval) {
        contrastLevel --;
        changeContrast();
      }
      break;
    case 3:
      if (joystickMovedRight() && brightnessLevel < maxInterval) {
        brightnessLevel ++;
        changeBrightness();
      } else if (joystickMovedLeft() && brightnessLevel > minInterval) {
        brightnessLevel --;
        changeBrightness();
      }
      break;
    case 4:
      if (joystickMovedRight() && matrixIntensityLevel < maxInterval) {
        matrixIntensityLevel ++;
        matrixIntensityMenu();
      } else if (joystickMovedLeft() && matrixIntensityLevel > minInterval) {
        matrixIntensityLevel --;
        matrixIntensityMenu();
      }
      break;
  }
}
// BACK
void back() {
  settingsMenuOpened = false;
  subSettingsMenuOpened = false;
}
void saveSettings() {
  // save settings to EEPROM
  int value;
  switch (currentSettingsMenu) {
    case 0:
      value = difficultyLevel;
      break;
    case 1:
      if (mute == true) {
        value = 0;
      } else {
        value = 1;
      }
      break;
    case 2:
      value = contrastLevel;
      break;
    case 3:
      value = brightnessLevel;
      break;
    case 4:
      value = matrixIntensityLevel;
      break;
  }
  EEPROM.update(currentSettingsMenu, value);
}
void updateSettingsMenu() {
  // iterate through settings menu options
  if (subSettingsMenuOpened == true) {
    changeValuesSubSettingsMenu();
    if (joystickPressed()) {
      saveSettings();
      settingsMenu();
    }
  } else if (joystickMovedDown()) {
    currentSettingsMenu ++;
    if (currentSettingsMenu > maxValueSettingsMenu) {
      currentSettingsMenu = minValueSettingsMenu;
    }
    settingsMenu();
  } else if (joystickMovedUp()) {
    currentSettingsMenu --;
    if (currentSettingsMenu < minValueSettingsMenu) {
      currentSettingsMenu = maxValueSettingsMenu;
    }
    settingsMenu();
  } else if (joystickMovedRight() && settingsMenuOpened) {
    changeSubSettingsMenu();
  } else if (joystickMovedLeft() && subSettingsMenuOpened) {
    settingsMenu();
  }
}
