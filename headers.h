class Pos {
  public:
  int x, y;
  Pos();
  Pos( int i, int j);
  bool operator==(const Pos &other );
  Pos operator+(const Pos &other );
  Pos operator-(const Pos &other );
};


const char *level_data[] = { 
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
  "W  W                                   W",
  "W  W                                   W",
  "W  W  W  WWWWWWWWWW                    W",
  "W  W  W  W        W                    W",
  "W  W  W  W        W                    W",
  "W  WWWWWWW        WWWW                 W",
  "W                                      W",
  "W                                      W",
  "W  WWWWWWW        WWWW                 W",
  "W        W        W  W                 W",
  "W        W        W  W                 W",
  "W        WWWW  WWWW  W                 W",
  "W           W  W     W                 W",
  "W           W  W     W                 W",
  "W           W  W     W                 W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW@W"
};

class Level {
  public:
    int width;
    int height;
    const char **data;
    void drawLevel();
    Level(int w, int h, const char **d);
    bool collides_with(Pos position, int size);
};

class Player {
  public:
  Pos position;
  Pos old_position;
  Player(int i, int j);
  void drawPlayer();
  void rotateAroundDoor(Pos center);
};


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
    bool collides_with(Pos position, int size);
    void draw();
    void rotate(bool direction);
    void check_and_rotate();
};

const int NUM_DOORS = 1;
Door doors[NUM_DOORS] = { Door(30, 30, true, false, true, false) };

static void finish(int sig);

uint64_t frame_start;

const int PLAYER_SIZE = 2;

const int FRAMES_PER_SECOND = 60;
const float MILL_PER_FRAME = 1000.0f / FRAMES_PER_SECOND;
const uint64_t MICRO_PER_FRAME =  MILL_PER_FRAME * 1000;


