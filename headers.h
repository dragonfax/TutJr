#include <stdbool.h>
#include "Arduboy.h"


extern Arduboy arduboy;



void drawString(byte x, byte y, const char* str);
void end(const char *str) ;

// A CELL is one square unit of wall, in the level bitmap.
// Here we define how many pixels on cell is.
//
// Also swinging door segments are 2,1 cells.
// And the player, and monsters are 2,2 cells.
//
// Some initializations and calculations are done in cell coordinates,
// instead of screen coordinates, for convenience.
const byte CELL = 4;

typedef unsigned char byte;

typedef unsigned int uint;

class Pos;

bool collision(Pos pa, byte wa, byte ha, Pos pb, byte wb, byte hb);
bool enclosure(Pos pa, byte wa, byte ha, Pos pb, byte wb, byte hb);

Pos cell_to_screen(Pos cell);
Pos screen_to_cell(Pos position);

class Pos {
  public:
  // Pos can be negative. so byte won't cut it.
  // Fortunately everything is within screen space so less than 128.
  char x, y; 
  Pos();
  Pos( char x, char y);
  bool operator==(const Pos &other );
  Pos operator+(const Pos &other );
  Pos operator-(const Pos &other );
};

extern const byte LEVEL_CELL_WIDTH;
extern const byte LEVEL_CELL_HEIGHT;

class Level {
  public:
    void draw();
    bool collides_with(Pos position, byte w, byte h);
    Level();
    void drawWallOutline(byte x, byte y);
    bool getWall(byte cell_x, byte cell_y);
};

extern Level level;

class Door;

class Player {
  public:
    Pos position;
    Pos old_position;
    byte direction;
    byte anim_frame;
    byte moveSteps;

    Player(byte cell_x, byte cell_y);
    void draw();
    Player();
    void move();
    void moveTo(Pos new_position);
    bool canMoveTo(Pos new_position);
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
    Door(byte cell_x, byte cell_y, byte doors);
    bool collides_with(Pos position, byte w, byte h);
    bool collides_with_pivot(Pos position, byte w, byte h);
    static bool doors_collides_with_pivot(Pos position, byte w, byte h);
    void draw();
    void swing(bool direction);
    void check_and_rotate();
    Pos rotatePos(Pos position);
};

extern const byte NUM_DOORS;
extern Door level_doors[];

const byte PLAYER_WIDTH = 2 * CELL;
const byte PLAYER_HEIGHT = 2 * CELL;


class Monster {
  public:
    Pos position;
    Pos old_position;
    byte direction;
    byte anim_frame;
    byte last_direction;
    Monster();
    Monster(byte cell_x, byte cell_y);
    void move();
    void draw();
    bool collides_with(Pos position, byte w, byte h);
    void setup();
};

const byte MONSTER_WIDTH = 2 * CELL;
const byte MONSTER_HEIGHT = 2 * CELL;

extern const byte NUM_MONSTERS;
extern Monster monsters[];


class Exit {
  public:
    Pos position;
    Exit();
    Exit(byte cell_x, byte cell_y);
    bool collides_with(Pos position, byte w, byte h);
    void draw();
};

extern Exit exitSpace;

extern const byte data[];