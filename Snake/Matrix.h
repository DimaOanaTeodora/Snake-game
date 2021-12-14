#include "LedControl.h" 
/* Changing the matrix view due to the position of the LCD
 * (7,7)......(7,0)
 *  .            .
 *  .            .
 * (0,7)......(0,0)
 *  ---- LCD -----
*/
// MATRIX
const int dinPin = 13; 
const int clockPin = 8;
const int loadPin = 10;
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER

byte matrixIntensityLevel = 1;
const double matrixIntensityValue = 0.5;
const byte matrixSize = 8;
bool animationHeart = true;

// Graphics
const byte emptyHeart[] = {B11111111,B11100111,B11000011,B10000001,B00000000,B00000000,B10011001,B11111111}; 
const byte fullHeart[] = {B00000000,B00011000,B00111100,B01111110,B11111111,B11111111,B01100110,B00000000};
const byte exclamationMark[] = {B00000000,B00001000,B00000000,B00001000,B00001000,B00001000,B00001000,B00000000};
const byte questionMark[] = {B00000000,B00001000,B00000000,B00001000,B00001000,B00010000,B00010100,B00011100}; 
const byte down[] = {B00000000,B00011000,B00111100,B01100110,B11000011,B10000001,B00000000,B00000000}; 
const byte up[] = {B00000000,B00000000,B10000001,B11000011,B01100110,B00111100,B00011000,B00000000}; 
const byte left[] = {B00110000,B00011000,B00001100,B00000110,B00000110,B00001100,B00011000,B00110000};
const byte right[] = {B00001100,B00011000,B00110000,B01100000,B01100000,B00110000,B00011000,B00001100};
const byte empty[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
const byte hi[] = {B00000000,B00000000,B00101010,B00101010,B00101110,B00001010,B00101010,B00000000};
const byte three[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100100,B00111100,B00000000};
const byte two[] = {B00000000,B01111000,B00001000,B00010000,B00100000,B00100100,B00111000,B00000000};
const byte one[] = {B00000000,B00111000,B00010000,B00010000,B00010100,B00011000,B00010000,B00000000};

//Functions
void updateMatrixDisplay(const byte matrix[]){
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
