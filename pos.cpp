#include "headers.h"

Pos::Pos() {
  x = 0;
  y = 0;
}

Pos::Pos(int i, int j) {
  x = i;
  y = j;
}

bool Pos::operator==(const Pos &other ) {
  return x == other.x && y == other.y ;
}

Pos Pos::operator+(const Pos &other ) {
  return Pos(x + other.x, y + other.y);
}

Pos Pos::operator-(const Pos &other) {
  return Pos(x - other.x, y - other.y);
}


