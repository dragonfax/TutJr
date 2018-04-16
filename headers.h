#include <stdbool.h>
#include "Arduboy.h"


extern Arduboy arduboy;



void drawString(byte x, byte y, const char* str);
void end(const char *str) ;

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
  char* to_string();
  ScreenPos operator+(const ScreenPos &other );
  ScreenPos operator-(const ScreenPos &other );
};

extern const byte LEVEL_WIDTH;
extern const byte LEVEL_HEIGHT;
extern const byte LEVEL_ROW_WIDTH;

class Entity {
  public:
    virtual ScreenPos get_position() = 0;
};

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

class Player : public Entity {
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

    ScreenPos get_position();
};

extern Player player;

const byte SPACE_SIZE=8;
const byte WALL_THICK=1;


enum Direction {
  VERTICAL = 1,
  HORIZONTAL
};

class Door{
  public:
    Door(MapPos position, Direction direction);
    ScreenPos center;
    Direction direction;
    bool collides_with(ScreenPos position, ScreenPos size, Entity* entity);
    bool collides_with_pivot(ScreenPos position, ScreenPos size);
    static bool doors_collides_with_pivot(ScreenPos position, ScreenPos size);
    void draw();
    void swing();
    // void check_and_rotate();
    static bool doors_collides_with_door(ScreenPos position, ScreenPos size, Entity* entity);
};

extern const byte NUM_DOORS;
extern Door level_doors[];

const byte PLAYER_WIDTH = SPACE_SIZE;
const byte PLAYER_HEIGHT = SPACE_SIZE;
const ScreenPos PLAYER_SIZE = ScreenPos(PLAYER_WIDTH,PLAYER_HEIGHT);


class Monster: public Entity {
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
    bool collides_with(ScreenPos position, ScreenPos size, Entity* entity);
    void setup();
    bool operator== ( Monster & rhs );
    static bool collides_with_any(ScreenPos position, ScreenPos size, Entity* entity);
    ScreenPos get_position();
};

const byte MONSTER_WIDTH = SPACE_SIZE;
const byte MONSTER_HEIGHT = SPACE_SIZE;
    
extern const byte NUM_MONSTERS;
extern Monster monsters[];

        
class Exit: public Entity {
  public:
    ScreenPos position;
    Exit();
    Exit(MapPos position);
    bool collides_with(ScreenPos position, ScreenPos size);
    void draw();
    ScreenPos get_position();
};

extern Exit exitSpace;

class SafeSpot: public Entity {
  public:
    ScreenPos position;
    SafeSpot();
    SafeSpot(MapPos position);
    ~SafeSpot() {};
    bool collides_with(ScreenPos position, ScreenPos size);
    ScreenPos get_position();
};

extern byte num_lives;
void lives_draw();

extern SafeSpot safeSpot;

extern const byte data[];