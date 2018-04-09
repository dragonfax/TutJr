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



