#include <LiquidCrystal.h>
//LCD
const byte RS = 13;
const byte enable = 8;
const byte d4 = 5;
const byte d5 = 4;
const byte d6 = 3;
const byte d7 = 2;
const byte contrastPin = 6;
const byte brightnessPin = 9;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

int contrastValue= 110;
int brightnessValue = 28836;
byte brightnessLevel = 2;
byte minInterval = 1;
byte maxInterval = 3;

// Joystick - Switch
const int joyX = A0;
const int joyY = A1;
const int pinSw = 7;
const int minTreshold = 350;
const int maxTreshold = 550;
int xValue = 0;
int yValue = 0;
bool switchState = LOW; //Joystick button

void setup() 
{
  lcd.begin(16, 2);
  lcd.clear();
  
  pinMode(RS, OUTPUT);
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(pinSw, INPUT_PULLUP);
  
  analogWrite(contrastPin, contrastValue);
  analogWrite(brightnessPin, brightnessValue); 

  brightnessMenu();
  changeBrightness();

  Serial.begin(9600);
}
void brightnessMenu(){
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Brightness ");

  lcd.setCursor(1,1);
  lcd.print("Press for EXIT");

}
void changeBrightness(){
  analogWrite(brightnessPin, brightnessValue + brightnessLevel * 100);
  lcd.setCursor(12, 0);
  lcd.print(brightnessLevel);
  lcd.print("/3");
}
void save(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Was saved");
}
void loop() 
{
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  switchState = digitalRead(pinSw);

  if(ifJoystickPressed()){
    save();
  }
  if(ifJoystickMovedRight() && brightnessLevel < maxInterval){
      brightnessLevel ++;
      changeBrightness();
   }else if(ifJoystickMovedLeft() && brightnessLevel > minInterval){
      brightnessLevel --;
      changeBrightness();
   }

   delay(250);
  
}
bool ifJoystickPressed(){
   if(switchState == LOW){
      return true;
   }
   return false;
}
bool ifJoystickMovedUp(){
  if(yValue >= minTreshold){
    return false;
  }else if(yValue < minTreshold){
    return true;
  }
}
bool ifJoystickMovedDown(){
  if(yValue <= maxTreshold){
    return false;
  }else if(yValue > maxTreshold){
    return true;
  }
}
bool ifJoystickMovedRight(){
  if(xValue <= maxTreshold){
    return false;
  }else if(xValue > maxTreshold){
    return true;
  }
}
bool ifJoystickMovedLeft(){
  if(xValue >= minTreshold){
    return false;
  }else if(xValue < minTreshold){
    return true;
  }
}
