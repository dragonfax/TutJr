#include "headers.h"


const byte LEVEL_WIDTH = 32;
const byte LEVEL_HEIGHT = 16;

static const byte PROGMEM data[] = { 
  B11111111,B11111111,B11111111,B11111111,
  B10010000,B00000000,B00000100,B00010001,
  B10010000,B00000000,B00000100,B00010001,
  B10010010,B01111111,B11100111,B10010011,
  B10010010,B01000000,B00100000,B10010010,
  B10010010,B01000000,B00100000,B10010010,
  B10011111,B11000000,B00111100,B10010010,
  B10000000,B00000000,B00000000,B00010010,
  B10000000,B00000000,B00000000,B00010010,
  B10011111,B10000000,B00111100,B11110010,
  B10000000,B01000000,B00100100,B10000001,
  B10000000,B01000000,B00100100,B10000001,
  B10000010,B01111001,B11100100,B11110010,
  B10010010,B00001001,B00000100,B10000010,
  B10010010,B00001001,B00000100,B10000010,
  B11111111,B11111111,B11111111,B11111111
};

Level::Level(byte w, byte h) {
  width = w;
  height = w;
}

Level::Level(){}

bool Level::getData(byte x, byte y) {

  byte by = y * 4;
  byte xb = x / 8;
  byte xm = 7 - x % 8;
  
  byte b = pgm_read_byte_near(data + (by + xb));
  byte mask = 1 << xm;
  
  return ( b & mask ) > 0;
}

void Level::drawLevel() {
  byte i;
  byte j;
  for ( i = 0; i < width; i++ ) {
    for ( j = 0; j < height; j++ ) {
      if ( getData(i,j) ) {
        drawCellWalls(j,i);
      }
    }
  }
}

void Level::drawCellWalls(byte y, byte x) {

  // north wall
  if ( y == 0 || !getData(x, y - 1) ) {
    arduboy.drawFastHLine(x * 4, y * 4, 4, 1);
  }

  // west wall
  if ( x == 0 || !getData(x - 1,y) ) {
    arduboy.drawFastVLine(x * 4, y * 4, 4, 1);
  }

  // south wall
  if ( y == 128 || !getData(x,y + 1) ) {
    arduboy.drawFastHLine( x * 4, y * 4 + 3, 4, 1);
  }

  // east wall
  if ( x == 32 || !getData(x + 1,y) ) {
    arduboy.drawFastVLine( x * 4 + 3, y * 4, 4, 1 );
  }


}

bool Level::collides_with(Pos position, byte w, byte h) {

  byte i, j;
  bool collision = false;
  for ( i = 0; i < h; i++ ) {
    for ( j = 0; j < w; j++ ) {
      if ( getData(position.x + j,position.y + i) ) {
        return true;
      }
    }
  }
  return false;
}



