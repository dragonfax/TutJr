#include "headers.h"
#include <curses.h>

const char *level_data[] = { 
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
  "W  W                 W     W           W",
  "W  W                 W     W           W",
  "W  W  W  WWWWWWWWWW  WWWW  W  WWWWWWW  W",
  "W  W  W  W        W     W  W  W     W  W",
  "W  W  W  W        W     W  W  W     W  W",
  "W  WWWWWWW        WWWW  W  W  W  WWWW  W",
  "W                          W  W     W  W",
  "W                          W  W     W  W",
  "W  WWWWWWW        WWWW  WWWW  W  W  W  W",
  "W  W     W        W  W  W        W  W  W",
  "W  W     W        W  W  W        W  W  W",
  "W  W  W  WWWW  WWWW  W  WWWW  W  W  W  W",
  "W  W  W     W  W     W  W     W     W  W",
  "W  W  W     W  W     W  W     W     W  W",
  "W  W  W  WWWW  WWWWWWW  W     W  W  W  W",
  "W  W  W  W                    W  W  W  W",
  "W  W  W  W                    W  W  W  W",
  "W  W  W  WWWWWWW  WWWWWWWWWWWWW  W WW  W",
  "W  W  W  W                             W",
  "W  W  W  W                             W",
  "W  W  W  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
  "W     W                                W",
  "W     W                                W",
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
  "W     W                                W",
  "W     W                                W",
  "W  W  WWWWWWW  WWWWWWWWWW              W",
  "W  W  W                 W              W",
  "W  W  W                 W              W",
  "W  W  W  WWWWWWWWWWWWW  W              W",
  "W  W                    W              W",
  "W  W                    W              W",
  "W  W  W  W  WWWWWWW  WWWW              W",
  "W  W  W  W  W           W              W",
  "W  W  W  W  W           W              W",
  "W  W  W  W  WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
  "W     W                                W",
  "W     W                                W",
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW@W"
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
      mvaddch(j,i, data[j][i]);
    }
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



