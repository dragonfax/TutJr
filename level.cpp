#include "headers.h"

Level level = Level();

const byte LEVEL_WIDTH = 32;
const byte LEVEL_HEIGHT = 16;

Level::Level(){}

bool Level::getWall(byte cell_x, byte cell_y) {

  // calculate bit that represents this wall.
  byte by = cell_y * 4;
  byte xb = cell_x / 8;
  byte xm = 7 - cell_x % 8;
  
  byte b = pgm_read_byte_near(data + (by + xb));
  byte mask = 1 << xm;
  
  return ( b & mask ) > 0;
}

bool isLocationWall(byte x, byte y) {
  return x%3 == 0 || y%3 == 0;
}

bool isHorizontalWall(byte x, byte y) {
  return y%3 != 0 && x%3 == 0;
}

bool isVerticalWall( byte x, byte y) {
  return x%3 != 0 && y%3 == 0;
}

const byte SPACE_SIZE=4;
const byte WALL_THICK=1;

void drawHorizontalWall(byte cell_x, byte cell_y) {
  Pos pos = cell_to_screen(Pos(cell_x, cell_y));
  arduboy.drawFastHLine(pos.x, pos.y, SPACE_SIZE, WHITE);
}
 
void drawVerticalWall(byte cell_x, byte cell_y) {
  Pos pos = cell_to_screen(Pos(cell_x, cell_y));
  arduboy.drawFastVLine(pos.x, pos.y, SPACE_SIZE, WHITE);
}
 
void drawCornerWall(byte cell_x, byte cell_y) {
  Pos pos = cell_to_screen(Pos(cell_x, cell_y));
  arduboy.drawFastHLine(pos.x, pos.y, WALL_THICK, WHITE);
}

void Level::draw() {
  for ( byte x = 0; x < LEVEL_WIDTH; x++ ) {
    for ( byte y = 0; y < LEVEL_HEIGHT; x++ ) {
      if ( isLocationWall(x,y) && getWall(x,y) ) {
        if ( isHorizontalWall(x,y) ) {
          drawHorizontalWall(x,y);
        } else if ( isVerticalWall(x,y) ) {
          drawVerticalWall(x,y);
        } else {
          drawCornerWall(x,y);
        }
      }
    }
  }
}

bool Level::collides_with(Pos position, byte w, byte h) {

  // find all the cells this shape overlaps with
  // check each for a wall segment

  Pos ul = position; // upper left
  Pos lr = position + Pos(w - 1, h - 1); // lower right

  Pos cell_ul = screen_to_cell(ul);
  Pos cell_lr = screen_to_cell(lr);

  byte i, j;
  for ( i = cell_ul.x; i <= cell_lr.x; i++ ) {
    for ( j = cell_ul.y; j <= cell_lr.y; j++ ) {
      if ( getWall(i,j) ) {
        return true;
      }
    }
  }
  return false;
}



