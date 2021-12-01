#include<LiquidCrystal.h>
#include<EEPROM.h>

//LCD
const int RS = 9;
const int enable = 8;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

// Joystick - Switch
const int joyX = A1;
const int joyY = A0;
const int pinSw = 7;
const int minTreshold = 505;
const int maxTreshold = 480;
int xValue = 0;
int yValue = 0;
bool switchState = LOW; //Joystick button
bool joyMoved = false;

//Game variables
bool gameHasStarted = false;
int memoryIndexCounter = 0;

void setup(){
  //loadMemory();//temporarely
  memoryIndexCounter = EEPROM.read(0);
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  
  pinMode(RS, OUTPUT);

  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);
  pinMode(pinSw, INPUT);
  
  //LCDIntro();
  //LCDGame(1, 0);
  //LCDGameOver();

  highScoreMenu();
  
  Serial.begin(9600);
}

void LCDIntro() {
  /*
  Set LCD screen greetings message:
      ~SNAKE~
        Hi!
  */
  lcd.clear();
  
  lcd.setCursor(4, 0);
  lcd.print("~SNAKE~");
  
  lcd.setCursor(6, 1);
  lcd.print("Hi!");

  delay(2000);
}

void ScrollMenu(){
   /*
   Move to scroll
   START
   HIGH SCORE
   SETTINGS
    ENTER NAME
    DIFICULTY 
    LCD CONTRAST
    LCD BRIGHTNESS
    MATRIX BRIGHTNESS
    CHOOSE THEME SONG (*)
   ABOUT
      SCROLLING TEXT (*)
  */
  lcd.clear();
  
  
}

void highScoreMenu(){
   /*
      HIGH SCORE: x
      <<back
  */
  lcd.clear();
  
  lcd.setCursor(1, 0);
  lcd.print("HIGH SCORE: ");
  lcd.print(returnHighScore());
  
  lcd.setCursor(0, 1);
  lcd.print("<<back");
}

void LCDGame(int currentLevel, int currentScore) { 
   /*
  Set LCD screen during a game:
      LEVEL x   Best
        Score y   zzz
  */
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("LEVEL ");
  lcd.print(currentLevel);
  
  lcd.setCursor(0, 1);
  lcd.print("Score ");
  lcd.print(currentScore);
  
  lcd.setCursor(10, 0);
  lcd.print("Best");
  
  lcd.setCursor(10, 1);
  lcd.print(returnHighScore());
}

void LCDGameOver(){
  /*
  Set LCD screen when a game is over:
      Move to
       try again
  */
  lcd.clear();
  
  lcd.setCursor(4, 0);
  lcd.print("Move to");
  
  lcd.setCursor(3, 1);
  lcd.print("try again");
  
}
int returnHighScore(){
  
  //read from EEPROM the high score 
  int maximum = -1;
  int value;
  for(int i=1; i<=memoryIndexCounter; i++){
    value = EEPROM.read(i);
    Serial.println(value);
    if(maximum < value){
      maximum = value;
    }
  }
  return maximum;
}
void verifyIfJoystickWasMoved(){
   if(xValue > minTreshold && xValue < maxTreshold &&joyMoved == true){
    joyMoved = false;
   }else if(yValue > minTreshold && yValue < maxTreshold &&joyMoved == true){
    joyMoved = false;
   }else if((xValue > minTreshold || yValue > minTreshold) && joyMoved == false){
    joyMoved = true;
    gameHasStarted = false;
    LCDGame(1, 0);
   }else if((xValue < maxTreshold || yValue < maxTreshold) && joyMoved == false){
    joyMoved = true;
    gameHasStarted = false;
    LCDGame(1, 0);
   }
}
void loop(){
   xValue = analogRead(joyX);
   yValue = analogRead(joyY);

   //Serial.println(xValue);
  //Serial.println(yValue);
   //verifyIfJoystickWasMoved();

}

/*temporarily function*/
void loadMemory(){
  EEPROM.write(1, 12);
  EEPROM.write(2, 20);
  EEPROM.write(3, 7);
  EEPROM.write(0,memoryIndexCounter+3); //Memory index counter on the 0 position
}
