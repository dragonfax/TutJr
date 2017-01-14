#include "headers.h"


void mvaddch(int x, int y, char c) {
      arduboy.drawChar(x,y, c, 1, 0, 1);
}

void refresh() {
  arduboy.display();
}

