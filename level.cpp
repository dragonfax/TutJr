#include "headers.h"

#include "generated/level1.cpp"

Level::Level( 
  byte width, 
  byte height, 
  byte row_width, 
  byte wall_data [], 
  byte num_monsters, 
  Monster monsters [], 
  byte num_doors, 
  Door doors [], 
  byte num_keys,
  Key keys [],
  Exit ex,
  Entrance entrance
){
  this->width = width;
  this->height = height;
  this->row_width = row_width;
  memcpy(this->wall_data, wall_data, 15 * 4);
  this->num_monsters = num_monsters;
  memcpy(this->monsters, monsters, sizeof(Monster) * MAX_MONSTERS);
  this->num_doors = num_doors;
  memcpy(this->doors, doors, sizeof(Door) * MAX_DOORS);
  this->num_keys = num_keys;
  memcpy(this->keys, keys, sizeof(Key) * MAX_KEYS);
  this->exit = ex;
  this->entrance = entrance;
  this->safeSpot = SafeSpot(screen_to_cell(entrance.position));
}

bool Level::getWall(MapPos cell) {

  // calculate bit that represents this wall.
  byte by = cell.y * row_width;
  byte xb = cell.x / 8;
  byte xm = 7 - cell.x % 8;
  
  byte b = wall_data[by + xb];
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
  for ( byte x = 0; x < this->width; x++ ) {
    for ( byte y = 0; y < this->height; y++ ) {
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



