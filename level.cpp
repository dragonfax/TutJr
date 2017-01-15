#include "headers.h"

Level level = Level();

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

Level::Level(){}

bool Level::getWall(byte cell_x, byte cell_y) {

  byte by = cell_y * 4;
  byte xb = cell_x / 8;
  byte xm = 7 - cell_x % 8;
  
  byte b = pgm_read_byte_near(data + (by + xb));
  byte mask = 1 << xm;
  
  return ( b & mask ) > 0;
}

void Level::draw() {
  byte i;
  byte j;
  for ( i = 0; i < LEVEL_WIDTH; i++ ) {
    for ( j = 0; j < LEVEL_HEIGHT; j++ ) {
      if ( getWall(i,j) ) {
        drawWallOutline(i,j);
      }
    }
  }
}

const byte WALL_SIZE = CELL;

void Level::drawWallOutline(byte cell_x, byte cell_y) {

  Pos pos = cell_to_screen(Pos(cell_x, cell_y));

  // north wall
  if ( cell_y == 0 || !getWall(cell_x, cell_y - 1) ) {
    arduboy.drawFastHLine(pos.x, pos.y, WALL_SIZE, WHITE);
  }

  // west wall
  if ( cell_x == 0 || !getWall(cell_x - 1,cell_y) ) {
    arduboy.drawFastVLine(pos.x, pos.y, WALL_SIZE, WHITE);
  }

  // south wall
  if ( cell_y == 128 || !getWall(cell_x,cell_y + 1) ) {
    arduboy.drawFastHLine( pos.x, pos.y + (WALL_SIZE - 1), WALL_SIZE, WHITE);
  }

  // east wall
  if ( cell_x == 32 || !getWall(cell_x + 1,cell_y) ) {
    arduboy.drawFastVLine( pos.x + (WALL_SIZE - 1), pos.y, WALL_SIZE, WHITE);
  }


}

bool Level::collides_with(Pos position, byte w, byte h) {

  // find all the cells this shape overlaps with
  // check each for a wall segment

  Pos ul = position; // upper left
  Pos lr = position + Pos(w, h); // lower right

  Pos cell_ul = screen_to_cell(ul);
  Pos cell_lr = screen_to_cell(lr);

  byte i, j;
  for ( i = cell_ul.x; i <= cell_lr.x; i++ ) {
    for ( j = cell_ul.y; j < cell_lr.y; j++ ) {
      if ( getWall(i,j) ) {
        return true;
      }
    }
  }
  return false;
}



