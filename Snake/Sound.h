// Variables
bool mute = false;
const int buzzerPin = A2;
//tone(A2, 200, 500);

// Functions
void menuSound(){
  if(!mute){
    tone(buzzerPin, 4978, 100);// 1865
  }
}
void eatSound(){
  if(!mute){
    tone(buzzerPin, 4186, 100);
  }
}
void colisionSound(){
  if(!mute){
    tone(buzzerPin, 139, 100);
  }
}
