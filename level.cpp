#include "headers.h"

Level level = Level();

const byte LEVEL_WIDTH = 32;
const byte LEVEL_HEIGHT = 16;

Level::Level(){}

bool Level::getWall(MapPos cell) {

  // calculate bit that represents this wall.
  byte by = cell.y * 4;
  byte xb = cell.x / 8;
  byte xm = 7 - cell.x % 8;
  
  byte b = pgm_read_byte_near(data + (by + xb));
  byte mask = 1 << xm;
  
  return ( b & mask ) > 0;
}

bool isLocationWall(MapPos cell) {
  return cell.x%3 == 0 || cell.y%3 == 0;
}

bool isHorizontalWall(MapPos cell) {
  return cell.x%3 != 0 && cell.y%3 == 0;
}

bool isVerticalWall( MapPos cell) {
  return cell.y%3 != 0 && cell.x%3 == 0;
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



