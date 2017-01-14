#include <stdbool.h>
#include "Arduboy.h"

extern Arduboy arduboy;

const int CELL_SIZE = 3;

void mvaddch(int y, int x, char c);
void refresh() ;

typedef unsigned char byte;

class Pos;

bool collision(Pos pa, int wa, int ha, Pos pb, int wb, int hb);
bool enclosure(Pos pa, int wa, int ha, Pos pb, int wb, int hb);

class Pos {
  public:
  int x, y;
  Pos();
  Pos( int i, int j);
  bool operator==(const Pos &other );
  Pos operator+(const Pos &other );
  Pos operator-(const Pos &other );
};

extern const char *level_data[];

const int LEVEL_WIDTH = 32;
const int LEVEL_HEIGHT = 16;

class Level {
  public:
    int width;
    int height;
    const char **data;
    void drawLevel();
    Level(int w, int h, const char **d);
    bool collides_with(Pos position, int w, int h);
    Level();
};

extern Level level;

class Door;

class Player {
  public:
  Pos position;
  Pos old_position;
  Player(int i, int j);
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
    Door(int x, int y, byte ds);
    bool collides_with(Pos position, int w, int h);
    void draw();
    void rotate(bool direction);
    void check_and_rotate();
};

const int NUM_DOORS = 2;
extern Door doors[NUM_DOORS];

const int PLAYER_WIDTH = 2;
const int PLAYER_HEIGHT = 2;


class Monster {
  public:
    Pos position;
    Pos old_position;
    byte direction;
    Monster();
    Monster(int x, int y);
    void move();
    void draw();
    bool collides_with(Pos position, int w, int h);
    void setup();
};

const int MONSTER_WIDTH = 2;
const int MONSTER_HEIGHT = 2;



const int NUM_MONSTERS = 1;
extern Monster monsters[NUM_MONSTERS];
