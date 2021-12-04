#include <LiquidCrystal.h>
//LCD
const int RS = 13;
const int enable = 8;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const int contrastPin = 6;
const int brightnessPin = 9;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

int contrastValue= 150;
int brightnessValue = 28836;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(RS, OUTPUT);
  
  analogWrite(contrastPin, contrastValue);
  analogWrite(brightnessPin, brightnessValue); 

  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Settings");
}

void loop() 
{
  
}
