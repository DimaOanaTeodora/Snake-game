// Variables
const int joyX = A0;
const int joyY = A1;
const int pinSw = 7;
const int minTreshold = 350;
const int maxTreshold = 550;
int xValue = 0;
int yValue = 0;
bool switchState = LOW; //Joystick button

// Functions
void readFromJoystick(){
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  switchState = digitalRead(pinSw);
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
    updateMatrixDisplay(up);
    return true;
  }
}
bool ifJoystickMovedDown(){
  if(yValue <= maxTreshold){
    return false;
  }else if(yValue > maxTreshold){
    updateMatrixDisplay(down);
    return true;
  }
}
bool ifJoystickMovedRight(){
  if(xValue <= maxTreshold){
    return false;
  }else if(xValue > maxTreshold){
    updateMatrixDisplay(right);
    return true;
  }
}
bool ifJoystickMovedLeft(){
  if(xValue >= minTreshold){
    return false;
  }else if(xValue < minTreshold){
    updateMatrixDisplay(left);
    return true;
  }
}