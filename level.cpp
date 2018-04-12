#include "headers.h"

Level level = Level();

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
  return x%2 == 1 || y%2 == 1;
}

bool isHorizontalWall(byte x, byte y) {
  return y%2 == 1 && x%2 == 0;
}

bool isVerticalWall( byte x, byte y) {
  return x%2 == 1 && y%2 == 1;
}

void Level::draw() {
  byte x;
  byte y;
  for ( x = 0; x < MAZE_MATRIX_WIDTH; x++ ) {
    for ( y = 0; y < MAZE_MATRIX_HEIGHT; x++ ) {
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

void Level::drawHorizontalWall(byte cell_x, byte cell_y) {
  Pos pos = cell_to_screen(Pos(cell_x, cell_y));
  arduboy.drawFastHLine(pos.x, pos.y, SPACE_SIZE, WHITE);
}

void Level::drawVerticalWall(byte cell_x, byte cell_y) {
  Pos pos = cell_to_screen(Pos(cell_x, cell_y));
  arduboy.drawFastVLine(pos.x, pos.y, SPACE_SIZE, WHITE);
}

void Level::drawCornerWall(byte cell_x, byte cell_y) {
  Pos pos = cell_to_screen(Pos(cell_x, cell_y));
  arduboy.drawFastHLine(pos.x, pos.y, WALL_THICK, WHITE);
}

/*

// an entity at a screen pos, could overlap with up to 4 different map locations.
byte entity_screen_to_map_positions(ScreenPos position, *MapPositions mapPositions) {
  MapPos mp = screen_to_map(position);
  add to list.
  byte num_positions = 1;

  mp1 = position + ScreenPos(SPACE_SIZE,0)
  if ( mp1 != mp ) {
    add it to list
  }

  mp2 = position + ScreenPos(0, SPACE_SIZE)
  if ( mp2 != mp ) { // have to check against hte other spaces too.
    add it to list
  }

  mp3 = position + ScreenPos(0, SPACE_SIZE)
  if ( mp3 != mp ) {
    add it to list
  }

  return num_positions;
}

// Entity at position collides with a map wall
bool Level::entity_collides_with(Pos position) {


  [4]MapPos mapPositions;
  num_positions = entity_screen_to_map_positions(position, &mapPositions);

  for ( int i = 0; i < num_positions; i++ ) {
    MapPos mp = mapPositions[i];
    if ( isWall(mp) ) {
      return true;
    }
  }
  return false;
}

*/

