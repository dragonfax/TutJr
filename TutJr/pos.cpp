#include "headers.h"

MapPos::MapPos() {
  x = 0;
  y = 0;
}

MapPos::MapPos(char i, char j) {
  x = i;
  y = j;
}

bool MapPos::operator==(const MapPos &other ) {
  return x == other.x && y == other.y ;
}

MapPos MapPos::operator+(const MapPos &other ) {
  return MapPos(x + other.x, y + other.y);
}

MapPos MapPos::operator-(const MapPos &other) {
  return MapPos(x - other.x, y - other.y);
}


ScreenPos::ScreenPos() {
  x = 0;
  y = 0;
}

ScreenPos::ScreenPos(char i, char j) {
  x = i;
  y = j;
}

bool ScreenPos::operator==(const ScreenPos &other ) {
  return x == other.x && y == other.y ;
}

ScreenPos ScreenPos::operator+(const ScreenPos &other ) {
  return ScreenPos(x + other.x, y + other.y);
}

ScreenPos ScreenPos::operator-(const ScreenPos &other) {
  return ScreenPos(x - other.x, y - other.y);
}

char* ScreenPos::to_string() {
  char buf1 [33];
  char buf2 [33];
  itoa(x, buf1, 10);
  itoa(y, buf2, 10);
  strcat(buf1,",");
  strcat(buf1,buf2);
  return buf1;
}

// Aligned with the very corner of a square.
bool ScreenPos::aligned() {
  MapPos mp = screen_to_cell(*this);
  return !isLocationWall(mp) && *this == cell_to_screen(mp);
}

byte cell_to_screen1d(byte x) {
  byte spaces = x / 2;
  byte walls = (x + 1)/ 2;
  return spaces * SPACE_SIZE + walls * WALL_THICK;
}

const byte UNIT_SIZE = SPACE_SIZE + WALL_THICK;

byte screen_to_cell1d(byte screen) {
  byte units = screen / UNIT_SIZE;
  byte remain = screen % UNIT_SIZE;

  byte extra = 0;
  if ( remain > 0 ) {
    extra = 1;
  }

  return units * 2 + extra;
}

ScreenPos cell_to_screen(MapPos cell) {
  return ScreenPos(cell_to_screen1d(cell.x), cell_to_screen1d(cell.y));
}

MapPos screen_to_cell(ScreenPos position) {
  return MapPos(screen_to_cell1d(position.x), screen_to_cell1d(position.y));
}
