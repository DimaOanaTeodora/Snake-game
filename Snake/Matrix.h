#include "LedControl.h" 
/*
 * (7,7)......(7,0)
 *  .            .
 *  .            .
 * (0,7)......(0,0)
*/
// LED matrix
const int dinPin = 13; 
const int clockPin = 8;
const int loadPin = 10;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER

byte matrixIntensityLevel = 1;
double matrixIntensityValue = 0.5;
const byte matrixSize = 8;

bool animationHeart = true;

// Graphics
byte emptyHeart[] = {B11111111,B11100111,B11000011,B10000001,B00000000,B00000000,B10011001,B11111111}; 
byte fullHeart[] = {B00000000,B00011000,B00111100,B01111110,B11111111,B11111111,B01100110,B00000000};
byte exclamationMark[] = {B00000000,B00001000,B00000000,B00001000,B00001000,B00001000,B00001000,B00000000};
byte questionMark[] = {B00000000,B00001000,B00000000,B00001000,B00001000,B00010000,B00010100,B00011100}; 
byte down[] = {B00000000,B00011000,B00111100,B01100110,B11000011,B10000001,B00000000,B00000000}; 
byte up[] = {B00000000,B00000000,B10000001,B11000011,B01100110,B00111100,B00011000,B00000000}; 
byte left[] = {B00110000,B00011000,B00001100,B00000110,B00000110,B00001100,B00011000,B00110000};
byte right[] = {B00001100,B00011000,B00110000,B01100000,B01100000,B00110000,B00011000,B00001100};
byte empty[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
byte hi[] = {B00000000,B00000000,B00101010,B00101010,B00101110,B00001010,B00101010,B00000000};
byte three[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100100,B00111100,B00000000};
byte two[] = {B00000000,B01111000,B00001000,B00010000,B00100000,B00100100,B00111000,B00000000};
byte one[] = {B00000000,B00111000,B00010000,B00010000,B00010100,B00011000,B00010000,B00000000};

//Functions
void updateMatrixDisplay(byte matrix[]){
  // show the icons on the matrix display 
  lc.clearDisplay(0);
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, matrix[row]);
  }
}
void animation(){
    if(!animationHeart){
      updateMatrixDisplay(fullHeart);
    }else{
      updateMatrixDisplay(emptyHeart);
    }
    animationHeart = !animationHeart;
}
