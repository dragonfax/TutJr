#include "headers.h"


// for reading the data structure
static constant byte MAZE_RECORD_WIDTH=8*3;

// number of spaces in the maze
static constant byte MAZE_SPACE_WIDTH=10;
static constant byte MAZE_SPACE_HEIGHT=5;

// number of locations in the map (spaces + walls)
static constant byte MAZE_MATRIX_WIDTH=MAZE_SPACE_WIDTH * 2 - 1;
static constant byte MAZE_MATRIX_HEIGHT=MAZE_SPACE_HEIGHT * 2 - 1;

static const byte PROGMEM data[] = { 
  B01000000,B00000100,B00000000,
  B01010111,B00011111,B00000000,
  B01010100,B00010001,B00000000,
  B01111100,B00011101,B01000000,
  B00000000,B00000000,B01000000,
  B01110000,B00011101,B11000000,
  B00000000,B00000101,B00000000,
  B00010111,B01000101,B11000000,
  B00010001,B01000101,B00000000,
};

const byte NUM_MONSTERS = 5;
Monster monsters[] = { Monster(13,7), Monster(10, 1), Monster(16, 10), Monster(22,13), Monster(10, 13) };

Player player = Player(0, 0);

SafeSpot safeSpot = SafeSpot(0, 0);

const byte NUM_DOORS = 5;
Door level_doors[] = { 
  Door(3, 12, DOOR_UP | DOOR_DOWN),
  Door(9, 9, DOOR_UP | DOOR_DOWN),
  Door(18, 12, DOOR_UP | DOOR_DOWN),
  Door(27, 3, DOOR_UP | DOOR_DOWN),
  Door(15, 3, DOOR_LEFT | DOOR_RIGHT)
};


Exit exitSpace = Exit(28,13);