#include <EEPROM.h>
/*
 * Save the top 3 high scores and the names
 * EEPROM = 0- leveldifficulty, 1- sound, 2- contrast LCD, 3- LCD bright, 4 -  matrix bright
 * HighScore (5,6,7), nameLenght(8,9,10), names(11,k,n) 
 * 
*/
void writeNewHighScoreToEEPROM(int highScore){
  // shift the other 2 
  EEPROM.update(7, EEPROM.read(6));
  EEPROM.update(6, EEPROM.read(5));
  EEPROM.update(5, highScore);
}
void writeNewNameLengthToEEPROM(int nameLength){
  // shift the other 2 
  EEPROM.update(10, EEPROM.read(9));
  EEPROM.update(9, EEPROM.read(8));
  EEPROM.update(8, nameLength);
}
String readStringFromEEPROM(int offset){
  // offset is the position in EEPROM of the length of the string you want to write
  byte len = EEPROM.read(offset);
  char data[len + 1];
  byte start;
  
  if(len > 0){
    if(offset == 8){
      start = 11;
    }else if(offset == 9){
      start = 11 + EEPROM.read(offset - 1);
    }else if(offset == 10){
      start = 11 + EEPROM.read(offset - 1) + EEPROM.read(offset - 2);
    }
    for (int i = 0; i < len; i++){
      data[i] = EEPROM.read(start + i);
    } 
  }
  data[len] = '\0';
  return String(data);
}
void writeNewStringNameToEEPROM(String player1){
  byte len1, len2, len3; 
  String player2 = readStringFromEEPROM(8);
  String player3 = readStringFromEEPROM(9);
  
  len1 = player1.length();
  len2 = player2.length();
  len3 = player3.length();
  writeNewNameLengthToEEPROM(len1);
  
  // player1's name
  for (int i = 0; i < len1; i++){
      EEPROM.update(11 + i, player1[i]);
  } 
  // player2's name
  for (int i = 0; i < len2; i++){
      EEPROM.update(11 + len1 + i, player2[i]);
  }
  // player3's name
  for (int i = 0; i < len3; i++){
      EEPROM.update(11 + len1 + len2 + i, player3[i]);
  }
}
void resetMemory(){
  // reset the top 3 scores to 0 
  // use it in dev :)
  /*EEPROM.update(0, 1); // LOW
  EEPROM.update(1, 0); // UNMUTE
  EEPROM.update(2, 1); // the best
  EEPROM.update(3, 2); // the best
  EEPROM.update(4, 1); // the best for my eyes :)*/
  
  EEPROM.update(5, 0);
  EEPROM.update(6, 0);
  EEPROM.update(7, 0);

  EEPROM.update(8, 0);
  EEPROM.update(9, 0);
  EEPROM.update(10, 0);
}
void saveHighScore(int highScore, String playerName){
  // save the new high score and the player name
  writeNewHighScoreToEEPROM(highScore);
  writeNewStringNameToEEPROM(playerName);
}
