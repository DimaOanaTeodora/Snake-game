// Joystick - Switch
const int joyX = A0;
const int joyY = A1;
const int pinSw = 7;
const int minTreshold = 350;
const int maxTreshold = 550;
int xValue = 0;
int yValue = 0;
bool switchState = LOW; //Joystick button
bool joyMoved = false;
bool joyMovedUp = false;
bool joyMovedDown = false;
bool joyMovedLeft = false;
bool joyMovedRight = false;

void verifyIfJoystickWasMoved(){
   if(joyMoved == true){
    if(xValue > minTreshold && xValue < maxTreshold){
      joyMoved = false;
     }else if(yValue > minTreshold && yValue < maxTreshold){
      joyMoved = false;
     }
   }
   if(joyMoved == false){
     if(xValue < minTreshold || yValue < minTreshold){
      joyMoved = true;
     }else if(xValue > maxTreshold || yValue > maxTreshold){
      joyMoved = true;
     }
   }
}
void verifyIfJoystickWasMovedUp(){
  if(yValue >= minTreshold){
    joyMovedUp = false;
  }else if(yValue < minTreshold){
    joyMovedUp = true;
  }
}
void verifyIfJoystickWasMovedDown(){
  if(yValue <= maxTreshold){
    joyMovedDown = false;
  }else if(yValue > maxTreshold){
    joyMovedDown = true;
  }
}
void verifyIfJoystickWasMovedRight(){
  if(xValue <= maxTreshold){
    joyMovedRight = false;
  }else if(xValue > maxTreshold){
    joyMovedRight = true;
  }
}
void verifyIfJoystickWasMovedLeft(){
  if(xValue >= minTreshold){
    joyMovedLeft = false;
  }else if(xValue < minTreshold){
    joyMovedLeft = true;
  }
}
