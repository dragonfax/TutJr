#include "headers.h"

Level level = Level();

Level::Level(){}

bool Level::getWall(MapPos cell) {

  // calculate bit that represents this wall.
  byte by = cell.y * LEVEL_ROW_WIDTH;
  byte xb = cell.x / 8;
  byte xm = 7 - cell.x % 8;
  
  byte b = pgm_read_byte_near(data + (by + xb));
  byte mask = 1 << xm;
  
  return ( b & mask ) > 0;
}

bool isOdd(byte x) {
  return x%2 == 1;
}

bool isEven(byte x) {
  return x%2 == 0;
}

bool isLocationWall(MapPos cell) {
  return isEven(cell.x) || isEven(cell.y);
}

bool isHorizontalWall(MapPos cell) {
  return isOdd(cell.x) && isEven(cell.y);
}

bool isVerticalWall( MapPos cell) {
  return isOdd(cell.y) && isEven(cell.x);
}

void drawHorizontalWall(MapPos cell) {
  ScreenPos pos = cell_to_screen(cell);
  arduboy.drawFastHLine(pos.x, pos.y, SPACE_SIZE, WHITE);
}
 
void drawVerticalWall(MapPos cell) {
  ScreenPos pos = cell_to_screen(cell);
  arduboy.drawFastVLine(pos.x, pos.y, SPACE_SIZE, WHITE);
}
 
void drawCornerWall(MapPos cell) {
  ScreenPos pos = cell_to_screen(cell);
  arduboy.drawFastHLine(pos.x, pos.y, WALL_THICK, WHITE);
}

void Level::draw() {
  for ( byte x = 0; x < LEVEL_WIDTH; x++ ) {
    for ( byte y = 0; y < LEVEL_HEIGHT; y++ ) {
      MapPos cell = MapPos(x,y);
      if ( isLocationWall(cell) && getWall(cell) ) {
        if ( isHorizontalWall(cell) ) {
          drawHorizontalWall(cell);
        } else if ( isVerticalWall(cell) ) {
          drawVerticalWall(cell);
        } else {
          drawCornerWall(cell);
        }
      }
    }
  }
}

bool Level::collides_with(ScreenPos position, ScreenPos size) {

  // find all the cells this shape overlaps with
  // check each for a wall segment

  ScreenPos ul = position; // upper left
  ScreenPos lr = position + size - ScreenPos(1, 1); // lower right

  MapPos cell_ul = screen_to_cell(ul);
  MapPos cell_lr = screen_to_cell(lr);

  byte i, j;
  for ( i = cell_ul.x; i <= cell_lr.x; i++ ) {
    for ( j = cell_ul.y; j <= cell_lr.y; j++ ) {
      MapPos cell = MapPos(i,j);
      if ( getWall(cell) ) {
        return true;
      }
    }
  }
  return false;
}



