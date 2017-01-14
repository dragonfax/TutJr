#include "headers.h"
#include <curses.h>

const char *level_data[] = { 
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
  "W  W                                   W",
  "W  W                                   W",
  "W  W  W  WWWWWWWWWW                    W",
  "W  W  W  W        W                    W",
  "W  W  W  W        W                    W",
  "W  WWWWWWW        WWWW                 W",
  "W                                      W",
  "W                                      W",
  "W  WWWWWWW        WWWW                 W",
  "W        W        W  W                 W",
  "W        W        W  W                 W",
  "W        WWWW  WWWW  W                 W",
  "W           W  W     W                 W",
  "W           W  W     W                 W",
  "W           W  W     W                 W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
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

bool Level::collides_with(Pos position, int size) {
  int i, j;
  bool collision = false;
  for ( i = 0; i < size; i++ ) {
    for ( j = 0; j < size; j++ ) {
      if ( level.data[position.y + i][position.x + j] != ' ' ) {
        collision = true;
      }
    }
  }
  return collision;
}



