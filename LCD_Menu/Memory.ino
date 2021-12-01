void returnHighScore(int &highScore, String &playerName){
  //read from EEPROM the high score 
  highScore = -1;
  /*int value;
  for(int i=1; i<=memoryIndexCounter; i+2){
    value = EEPROM.read(i);
    Serial.println(value);
    if(highScore < value){
      highScore = value;
      playerName = EEPROM.read(i+1); 
    }
  }*/
}
/*temporarily function*/
void loadMemory(){
  /*EEPROM.update(1, 12);
  EEPROM.update(2, "Ionel");
  EEPROM.update(3, 20);
  EEPROM.update(4, "Ana");
  EEPROM.update(5, 5);
  EEPROM.update(6, "Maria");
  EEPROM.update(0, 6); //Memory index counter on the 0 position*/
}
