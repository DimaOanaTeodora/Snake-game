#define NOTE_DS8 4978 
#define NOTE_C8 4186
#define NOTE_CS3 139
bool mute = false;
const int buzzerPin = A2;
const int duration = 100; //millis

void menuSound() {
  if(!mute) {
    tone(buzzerPin, NOTE_DS8, duration);
  }
}
void eatSound() {
  if(!mute) {
    tone(buzzerPin, NOTE_C8, duration);
  }
}
void colisionSound() {
  if(!mute) {
    tone(buzzerPin, NOTE_CS3, duration);
  }
}
