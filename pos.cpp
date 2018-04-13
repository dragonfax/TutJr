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

byte cell_to_screen1d(byte cell) {
  byte spaces = ( cell / 3.0 ) * 2;
  byte walls = (cell + 2) / 3; // div 3, but round up, not down.
  return spaces * SPACE_SIZE + walls * WALL_THICK;
}

const byte UNIT_SIZE = SPACE_SIZE * 2 + WALL_THICK;

byte screen_to_cell1d(byte screen) {
  byte units = screen / UNIT_SIZE;
  byte remain = screen % UNIT_SIZE;

  byte add = 0;
  if ( remain == WALL_THICK ) {
    add = 1;
  } else if ( remain == WALL_THICK + SPACE_SIZE ) {
    add = 2;
  } else {
    Serial.println("Error, bad size of cell1d");
  }

  return units * 3;
}

ScreenPos cell_to_screen(MapPos cell) {
  return ScreenPos(cell_to_screen1d(cell.x), cell_to_screen1d(cell.y));
}

MapPos screen_to_cell(ScreenPos position) {
  // return MapPos(position.x / CELL, position.y / CELL);
  return MapPos(screen_to_cell1d(position.x), screen_to_cell1d(position.y));
}
