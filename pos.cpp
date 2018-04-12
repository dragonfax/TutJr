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


ScreenPos cell_to_screen(MapPos cell) {
  return ScreenPos(cell.x * CELL, cell.y * CELL);
}

MapPos screen_to_cell(ScreenPos position) {
  return MapPos(position.x / CELL, position.y / CELL);
}
