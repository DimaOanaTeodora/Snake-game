bool mute = false;
const int buzzerPin = A2;

void menuSound(){
  if(!mute){
    tone(buzzerPin, 1865, 500);
  }
}
void eatSound(){
  if(!mute){
    tone(buzzerPin, 4186, 500);
  }
}
void stopSound(){
  noTone(buzzerPin);
}
