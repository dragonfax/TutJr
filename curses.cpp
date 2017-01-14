#include "headers.h"


void mvaddch(int y, int x, char c) {
      arduboy.drawChar(y,x, c, 1, 0, 1);
}

void refresh() {
  arduboy.display();
}

