//Variables
const int RS = 13;
const int enable = 8;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
const byte contrastPin = 6;
const byte brightnessPin = 9;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

int contrastValue= 105;
int brightnessValue = 28836;
byte brightnessLevel = 2;
byte contrastLevel = 1;
byte minInterval = 1;
byte maxInterval = 3;

void greetings() {
  lcd.clear();
  
  lcd.setCursor(4, 0);
  lcd.print("~SNAKE~");
  
  lcd.setCursor(6, 1);
  lcd.print("Hi!");

  updateMatrixDisplay(hi);
  delay(1500);
}
