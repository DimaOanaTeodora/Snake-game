#include <EEPROM.h>
/*
 * Save the top 3 high scores and the names
 * EEPROM = 0- leveldifficulty, 1- bright LCD, 2- contrast LCD, 3- bright matrix, 4 -  sound 
 * HighScore (0,1,2), nameLenght(3,4,5), names(6,k,n) 
 * 
*/
void writeNewHighScoreToEEPROM(int highScore){
  // shift the other 2 ( from 1 to 2, from 0 to 1)
  EEPROM.update(2, EEPROM.read(1));
  EEPROM.update(1, EEPROM.read(0));
  EEPROM.update(0, highScore);
}
void writeNewNameLengthToEEPROM(int nameLength){
  // shift the other 2 ( from 1 to 2, from 0 to 1)
  EEPROM.update(5, EEPROM.read(4));
  EEPROM.update(4, EEPROM.read(3));
  EEPROM.update(3, nameLength);
}
String readStringFromEEPROM(int offset){
  // offset is the position in EEPROM of the length of the string you want to write
  byte len = EEPROM.read(offset);
  char data[len + 1];
  byte start;
  
  if(len > 0){
    if(offset == 3){
      start = 6;
    }else if(offset == 4){
      start = 6 + EEPROM.read(offset - 1);
    }else if(offset == 5){
      start = 6 + EEPROM.read(offset - 1) + EEPROM.read(offset - 2);
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
  String player2 = readStringFromEEPROM(3);
  String player3 = readStringFromEEPROM(4);
  
  len1 = player1.length();
  len2 = player2.length();
  len3 = player3.length();
  writeNewNameLengthToEEPROM(len1);
  
  // player1's name
  for (int i = 0; i < len1; i++){
      EEPROM.update(6 + i, player1[i]);
  } 
  // player2's name
  for (int i = 0; i < len2; i++){
      EEPROM.update(6 + len1 + i, player2[i]);
  }
  // player3's name
  for (int i = 0; i < len3; i++){
      EEPROM.update(6 + len1 + len2 + i, player3[i]);
  }
}
void resetMemory(){
  // reset the top 3 scores to 0 
  // use it in dev :)
  EEPROM.update(0, 0);
  EEPROM.update(1, 0);
  EEPROM.update(2, 0);

  EEPROM.update(3, 0);
  EEPROM.update(4, 0);
  EEPROM.update(5, 0);
}
void saveHighScore(int highScore, String playerName){
  // save the new high score and the player name
  writeNewHighScoreToEEPROM(highScore);
  writeNewStringNameToEEPROM(playerName);
}
