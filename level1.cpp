#include "headers.h"

static const byte PROGMEM data[] = { 
  B11111111,B11111111,B11111111,B11111110,
  B10010000,B00000000,B00000100,B00000010,
  B10010000,B00000000,B00000100,B00000010,
  B10010010,B01111000,B00111111,B10000010,
  B10010010,B01000000,B00100000,B10000010,
  B10010010,B01000000,B00100000,B10000010,
  B10011111,B11000000,B00111100,B10010010,
  B10000000,B00000000,B00000000,B00010010,
  B10000000,B00000000,B00000000,B00010010,
  B10011110,B00000000,B00111100,B11110010,
  B10000000,B00000000,B00000100,B10000010,
  B10000000,B00000000,B00000100,B10000010,
  B10000010,B01111001,B00000100,B11110010,
  B10000010,B00001001,B00000100,B10000010,
  B10000010,B00001001,B00000100,B10000010,
  B11111111,B11111111,B11111111,B11111110
};

const byte NUM_MONSTERS = 5;
Monster monsters[] = { Monster(13,7), Monster(10, 1), Monster(16, 10), Monster(22,13), Monster(10, 13) };

Player player = Player(1, 1);

const byte NUM_DOORS = 5;
Door doors[] = { 
  Door(3, 12, DOOR_UP | DOOR_LEFT | DOOR_DOWN),
  Door(9, 9, DOOR_UP | DOOR_DOWN),
  Door(18, 12, DOOR_UP | DOOR_LEFT),
  Door(27, 3, DOOR_UP | DOOR_DOWN),
  Door(15, 3, DOOR_LEFT | DOOR_RIGHT)
};


Exit exitSpace = Exit(28,13);