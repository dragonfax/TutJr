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

class MapPos;
class ScreenPos;

bool collision(ScreenPos pa, ScreenPos sizea, ScreenPos pb, ScreenPos sizeb);
bool enclosure(ScreenPos pa, ScreenPos sizea, ScreenPos pb, ScreenPos sizeb);

ScreenPos cell_to_screen(MapPos cell);
MapPos screen_to_cell(ScreenPos position);

class MapPos {
  public:
  // Pos can be negative. so byte won't cut it.
  // Fortunately everything is within screen space so less than 128.
  char x, y; 
  MapPos();
  MapPos( char x, char y);
  bool operator==(const MapPos &other );
  MapPos operator+(const MapPos &other );
  MapPos operator-(const MapPos &other );
};

class ScreenPos {
  public:
  // Pos can be negative. so byte won't cut it.
  // Fortunately everything is within screen space so less than 128.
  char x, y; 
  ScreenPos();
  ScreenPos( char x, char y);
  bool operator==(const ScreenPos &other );
  ScreenPos operator+(const ScreenPos &other );
  ScreenPos operator-(const ScreenPos &other );
};

extern const byte LEVEL_CELL_WIDTH;
extern const byte LEVEL_CELL_HEIGHT;

class Level {
  public:
    void draw();
    bool collides_with(ScreenPos position, ScreenPos size);
    Level();
    void drawWallOutline(MapPos cell);
    bool getWall(MapPos cell);
};

extern Level level;

class Door;

class Player {
  public:
    ScreenPos position;
    ScreenPos old_position;
    byte direction;
    byte anim_frame;
    byte moveSteps;

    Player(MapPos cell);
    void draw();
    Player();
    void move();
    void moveTo(ScreenPos new_position);
    bool canMoveTo(ScreenPos new_position);
};

extern Player player;



const byte DOOR_UP = 1;
const byte DOOR_RIGHT = 2;
const byte DOOR_DOWN = 4;
const byte DOOR_LEFT = 8;

class Door {
  public:
    ScreenPos center;
    byte doors;
    byte collidedDoors;
    Door(MapPos position, byte doors);
    bool collides_with(ScreenPos position, ScreenPos size);
    bool collides_with_pivot(ScreenPos position, ScreenPos size);
    static bool doors_collides_with_pivot(ScreenPos position, ScreenPos size);
    void draw();
    void swing(bool direction);
    void check_and_rotate();
    ScreenPos rotatePos(ScreenPos position);
};

extern const byte NUM_DOORS;
extern Door level_doors[];

const byte PLAYER_WIDTH = 2 * CELL;
const byte PLAYER_HEIGHT = 2 * CELL;


class Monster {
  public:
    ScreenPos position;
    ScreenPos old_position;
    byte direction;
    byte anim_frame;
    byte last_direction;
    Monster();
    Monster(MapPos position);
    void move();
    void draw();
    bool collides_with(ScreenPos position, ScreenPos size);
    void setup();
    bool operator== ( Monster & rhs );
};

const byte MONSTER_WIDTH = 2 * CELL;
const byte MONSTER_HEIGHT = 2 * CELL;
    
extern const byte NUM_MONSTERS;
extern Monster monsters[];

        
class Exit {
  public:
    ScreenPos position;
    Exit();
    Exit(MapPos position);
    bool collides_with(ScreenPos position, ScreenPos size);
    void draw();
};

extern Exit exitSpace;

class SafeSpot {
  public:
    ScreenPos position;
    SafeSpot();
    SafeSpot(MapPos position);
    bool collides_with(ScreenPos position, ScreenPos size);
};

extern byte num_lives;
void lives_draw();

extern SafeSpot safeSpot;

extern const byte data[];