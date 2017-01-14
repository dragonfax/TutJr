#include "headers.h"

const char *level_data[] = { 
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
  "W  W                 W     W   W",
  "W  W                 W     W   W",
  "W  W  W  WWWWWWWWWW  WWWW  W  WW",
  "W  W  W  W        W     W  W  W ",
  "W  W  W  W        W     W  W  W ",
  "W  WWWWWWW        WWWW  W  W  W ",
  "W                          W  W ",
  "W                          W  W ",
  "W  WWWWWW         WWWW  WWWW  W ",
  "W        W        W  W  W      W",
  "W        W        W  W  W      W",
  "W     W  WWWW  WWWW  W  WWWW  W ",
  "W  W  W     W  W     W  W     W ",
  "W  W  W     W  W     W  W     W ",
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};


Level::Level(int w, int h, const char **d) {
  width = w;
  height = w;
  data = d;
}

Level::Level(){}

void Level::drawLevel() {
  int i;
  int j;
  for ( i = 0; i < width; i++ ) {
    for ( j = 0; j < height; j++ ) {
      if ( data[j][i] == 'W' ) {
        drawCellWalls(j,i);
      }
    }
  }
}

void Level::drawCellWalls(int y, int x) {

  if ( data[y - 1][x] != 'W' ) {
    arduboy.drawFastHLine(x * 4, y * 4, 4, 1);
  }

  if ( data[y][x - 1] != 'W' ) {
    arduboy.drawFastVLine(x * 4, y * 4, 4, 1);
  }

  if ( data[y + 1][x] != 'W' ) {
    arduboy.drawFastHLine( x * 4, y * 4 + 3, 4, 1);
  }

  if ( data[y][x + 1] != 'W' ) {
    arduboy.drawFastVLine( x * 4 + 3, y * 4, 4, 1 );
  }


}

bool Level::collides_with(Pos position, int w, int h) {

  int i, j;
  bool collision = false;
  for ( i = 0; i < h; i++ ) {
    for ( j = 0; j < w; j++ ) {
      if ( level.data[position.y + i][position.x + j] != ' ' ) {
        return true;
      }
    }
  }
  return false;
}



