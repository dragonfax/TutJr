#include <stdbool.h>

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

void finish(int i);


class Door {
  public:
    Pos center;
    bool up;
    bool flagUp;
    bool down;
    bool flagDown;
    bool left;
    bool flagLeft;
    bool right;
    bool flagRight;
    Door(int x, int y, bool u, bool d, bool l, bool r);
    bool collides_with(Pos position, int w, int h);
    void draw();
    void rotate(bool direction);
    void check_and_rotate();
};

const int NUM_DOORS = 1;
extern Door doors[NUM_DOORS];

const int PLAYER_WIDTH = 2;
const int PLAYER_HEIGHT = 2;
