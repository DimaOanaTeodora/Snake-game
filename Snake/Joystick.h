// Variables
const int joyX = A0;
const int joyY = A1;
const int pinSw = 7;
const int minTreshold = 350;
const int maxTreshold = 550;
int xValue = 0;
int yValue = 0;
bool switchState = HIGH; //Joystick button
bool lastSwitchState = HIGH; //Joystick button

// if game has started the matrix shows the snake else the matrix shows the arrows
bool gameHasStarted = false;

// Functions
void readFromJoystick(){
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  switchState = digitalRead(pinSw);
}
bool joystickPressed(){
   if(switchState == LOW){
      return true;
   }
   return false;
}
bool joystickMovedUp(){
  if(yValue >= minTreshold){
    return false;
  }else if(yValue < minTreshold){
    if(!gameHasStarted){
      updateMatrixDisplay(up);
      menuSound();
    }
    return true;
  }
}
bool joystickMovedDown(){
  if(yValue <= maxTreshold){
    return false;
  }else if(yValue > maxTreshold){
    if(!gameHasStarted){
      updateMatrixDisplay(down);
      menuSound();
    }
    return true;
  }
}
bool joystickMovedRight(){
  if(xValue <= maxTreshold){
    return false;
  }else if(xValue > maxTreshold){
    if(!gameHasStarted){
      updateMatrixDisplay(right);
      menuSound();
    }
    return true;
  }
}
bool joystickMovedLeft(){
  if(xValue >= minTreshold){
    return false;
  }else if(xValue < minTreshold){
    if(!gameHasStarted){
      updateMatrixDisplay(left);
      menuSound();
    }
    return true;
  }
}
