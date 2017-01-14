#include <stdbool.h>
#include "Arduboy.h"

extern Arduboy arduboy;

const byte CELL_SIZE = 4;

typedef unsigned char byte;

typedef unsigned int uint;

class Pos;

bool collision(Pos pa, byte wa, byte ha, Pos pb, byte wb, byte hb);
bool enclosure(Pos pa, byte wa, byte ha, Pos pb, byte wb, byte hb);

class Pos {
  public:
  char x, y;
  Pos();
  Pos( char i, char j);
  bool operator==(const Pos &other );
  Pos operator+(const Pos &other );
  Pos operator-(const Pos &other );
};

extern const char *level_data[];

const byte LEVEL_WIDTH = 32;
const byte LEVEL_HEIGHT = 16;

class Level {
  public:
    byte width;
    byte height;
    const char **data;
    void drawLevel();
    Level(byte w, byte h, const char **d);
    bool collides_with(Pos position, byte w, byte h);
    Level();
    void drawCellWalls(byte x, byte y);

};

extern Level level;

class Door;

class Player {
  public:
  Pos position;
  Pos old_position;
  Player(byte i, byte j);
  void drawPlayer();
  void rotateAroundDoor(Pos center);
  Player();
  void move(Level level, Door doors[]);
};

extern Player player;



const byte DOOR_UP = 1;
const byte DOOR_RIGHT = 2;
const byte DOOR_DOWN = 4;
const byte DOOR_LEFT = 8;

class Door {
  public:
    Pos center;
    byte doors;
    byte collidedDoors;
    Door(byte x, byte y, byte ds);
    bool collides_with(Pos position, byte w, byte h);
    void draw();
    void rotate(bool direction);
    void check_and_rotate();
};

const byte NUM_DOORS = 2;
extern Door doors[NUM_DOORS];

const byte PLAYER_WIDTH = 2;
const byte PLAYER_HEIGHT = 2;


class Monster {
  public:
    Pos position;
    Pos old_position;
    byte direction;
    Monster();
    Monster(byte x, byte y);
    void move();
    void draw();
    bool collides_with(Pos position, byte w, byte h);
    void setup();
};

const byte MONSTER_WIDTH = 2;
const byte MONSTER_HEIGHT = 2;



const byte NUM_MONSTERS = 1;
extern Monster monsters[NUM_MONSTERS];
