const int contrastValue= 70;
const int brightnessValue = 28836;
byte brightnessLevel = 2;
byte contrastLevel = 2;

//DIFFICULTY
void difficultyMenu() {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Mode ");
  lcd.setCursor(7, 0);
  lcd.print(difficulty[difficultyLevel-1]);
  lcd.setCursor(1,1);
  lcd.print("Press for EXIT");
}
//SOUND
void soundMenu() {
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("UNMUTE");
  lcd.setCursor(1,1);
  lcd.print("Press for EXIT");
}
void changeSound() {
  lcd.setCursor(4,0);
  lcd.print("      ");
  lcd.setCursor(4,0);
  if(mute) {
     lcd.print("MUTE");
  }else{
     lcd.print("UNMUTE");
  }
}
// LCD CONTRAST
void contrastMenu() {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Contrast ");
  lcd.setCursor(1,1);
  lcd.print("Press for EXIT");
}
void changeContrast() {
  analogWrite(contrastPin, contrastValue + contrastLevel * 16);
  lcd.setCursor(11, 0);
  lcd.print(contrastLevel);
  lcd.print("/3");
}
// LCD BRIGHTNESS
void brightnessMenu() {
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Brightness ");
  lcd.setCursor(1,1);
  lcd.print("Press for EXIT");
}
void changeBrightness() {
  analogWrite(brightnessPin, brightnessValue + brightnessLevel * 100);
  lcd.setCursor(12, 0);
  lcd.print(brightnessLevel);
  lcd.print("/3");
}
//MATRIX BRIGHTNESS 
void matrixIntensityMenu() {
  lc.setIntensity(0, matrixIntensityValue + matrixIntensityLevel);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Intensity ");
  lcd.setCursor(11, 0);
  lcd.print(matrixIntensityLevel);
  lcd.print("/3");
  lcd.setCursor(1,1);
  lcd.print("Press for EXIT");
}
