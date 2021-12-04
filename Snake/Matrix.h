#include "LedControl.h" 
/*
 * (7,7)......(7,0)
 *  .            .
 *  .            .
 * (0,7)......(0,0)
*/

// LED matrix
const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER

byte matrixIntensityLevel = 1;
double matrixIntensityValue = 0.5;
const byte matrixSize = 8;

//Functions
void updateMatrixDisplay(byte matrix[]) {
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, matrix[row]);
  }
}
// Graphics
byte down[matrixSize] = {
  B00000000,
  B00011000,
  B00111100,
  B01100110,
  B11000011,
  B10000001,
  B00000000,
  B00000000
}; 
byte up[matrixSize] = {
  B00000000,
  B00000000,
  B10000001,
  B11000011,
  B01100110,
  B00111100,
  B00011000,
  B00000000
}; 
byte left[matrixSize] = {
  B00110000,
  B00011000,
  B00001100,
  B00000110,
  B00000110,
  B00001100,
  B00011000,
  B00110000
};
 
byte right[matrixSize] = {
  B00001100,
  B00011000,
  B00110000,
  B01100000,
  B01100000,
  B00110000,
  B00011000,
  B00001100
};
byte empty[matrixSize] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
byte hi[matrixSize] = {
  B00000000,
  B00000000,
  B00101010,
  B00101010,
  B00101110,
  B00001010,
  B00101010,
  B00000000
};
byte three[matrixSize] = {
  B00000000,
  B00111100,
  B00100000,
  B00111000,
  B00100000,
  B00100100,
  B00111100,
  B00000000
};
byte two[matrixSize] = {
  B00000000,
  B01111000,
  B00001000,
  B00010000,
  B00100000,
  B00100100,
  B00111000,
  B00000000
};
byte one[matrixSize] = {
  B00000000,
  B00111000,
  B00010000,
  B00010000,
  B00010100,
  B00011000,
  B00010000,
  B00000000
};
