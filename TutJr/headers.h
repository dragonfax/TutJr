#include <stdbool.h>
#include <Arduboy2.h>

extern Arduboy2 arduboy;

void drawString(byte x, byte y, const char* str);
void end(const char *str) ;

bool isOdd(byte x);

typedef unsigned char byte;

typedef unsigned int uint;

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

bool isLocationWall(MapPos pos);

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
  bool aligned();
};

bool collision(ScreenPos pa, ScreenPos sizea, ScreenPos pb, ScreenPos sizeb);
bool enclosure(ScreenPos pa, ScreenPos sizea, ScreenPos pb, ScreenPos sizeb);

ScreenPos cell_to_screen(MapPos cell);
MapPos screen_to_cell(ScreenPos position);


class Entity {
  public:
    virtual ScreenPos get_position() = 0;
};

 
class Door;

class Player : public Entity {
  public:
    ScreenPos position;
    ScreenPos old_position;
    byte direction;
    byte anim_frame;
    bool moving;
    byte lives = 4;
    byte keys;

    Player(MapPos cell);
    void draw();
    Player();
    void move();
    void moveTo(ScreenPos new_position);
    bool canMoveTo(ScreenPos new_position);

    ScreenPos get_position();
    bool isSquare();
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
    Door(){};
    ScreenPos center;
    Direction direction;
    bool collides_with(ScreenPos position, ScreenPos size, Entity* entity, bool canPivot);
    bool collides_with_pivot(ScreenPos position, ScreenPos size);
    void draw();
    void swing();
    // void check_and_rotate();
};

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
    
class Exit: public Entity {
  public:
    ScreenPos position;
    Exit();
    Exit(MapPos position);
    bool collides_with(ScreenPos position, ScreenPos size);
    void draw();
    ScreenPos get_position();
};

class SafeSpot: public Entity {
  public:
    ScreenPos position;
    SafeSpot();
    SafeSpot(MapPos position);
    ~SafeSpot() {};
    bool collides_with(ScreenPos position, ScreenPos size);
    ScreenPos get_position();
};

class Entrance {
  public:
    ScreenPos position;
    Entrance();
    Entrance(MapPos position);
};

void lives_draw();
void keys_draw();

class Key {
  public:
    ScreenPos position;
    bool taken = false;
    Key(){};
    Key(MapPos position) { this->position = cell_to_screen(position); };
    static void check_any_collides(ScreenPos pos, ScreenPos size);
    bool collides_with(ScreenPos position, ScreenPos size) ;
    void draw();
};

void gates_draw();

class Gate {
  public:
    ScreenPos position;
    bool opened = false;
    Gate() {};
    Gate(MapPos position) { this->position = cell_to_screen(position); };
    static bool check_any_collides(ScreenPos pos, ScreenPos size);
    bool collides_with(ScreenPos position, ScreenPos size) ;
    void draw();
};

const byte MAX_DOORS = 20;
const byte MAX_MONSTERS = 20;
const byte MAX_KEYS = 5;
const byte MAX_GATES = 5;

class Level {
  public:
    Level( 
      byte width, 
      byte height, 
      byte row_width, 
      byte wall_data [], 
      byte num_monsters, 
      Monster monsters [], 
      byte num_doors, 
      Door doors [], 
      byte num_keys,
      Key keys [],
      byte num_gates,
      Gate gates [],
      Exit exit, 
      Entrance entrance
    );
    void draw();
    bool collides_with(ScreenPos position, ScreenPos size);
    Level();
    void drawWallOutline(MapPos cell);
    bool getWall(MapPos cell);
    bool doors_collides_with_pivot(ScreenPos position, ScreenPos size);
    bool doors_collides_with_door(ScreenPos position, ScreenPos size, Entity* entity, bool canPivot);

    byte width ;
    byte height ;
    byte row_width ;
    byte wall_data [15 * 4];
    byte num_monsters ;
    Monster monsters [MAX_MONSTERS];
    byte num_doors ;
    Door doors [MAX_DOORS];
    byte num_keys;
    Key keys [MAX_KEYS];
    byte num_gates;
    Gate gates [MAX_GATES];
    Exit exit ;
    Entrance entrance;
    SafeSpot safeSpot;
};

extern Level level;

void respawn();

void win();
 