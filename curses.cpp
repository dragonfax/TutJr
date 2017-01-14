#include "headers.h"


void mvaddch(int y, int x, char c) {
      arduboy.drawChar(y * 4,x * 4, c, 1, 0, 1);
}

void refresh() {
  arduboy.display();
}

