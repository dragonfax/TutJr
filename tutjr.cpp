
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

class Pos {
  public:
  int x, y;
  Pos();
  Pos( int i, int j);
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
  "W                            CDD       W",
  "W                            D         W",
  "W                            D         W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W            D                         W",
  "W            D                         W",
  "W            C         DDCDD           W",
  "W            D                         W",
  "W            D                         W",
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
    bool collides_with(Pos position);
};

Level::Level(int w, int h, const char **d) {
  width = w;
  height = w;
  data = d;
}

Level level = Level(40, 40, level_data);

void Level::drawLevel() {
  int i;
  int j;
  for ( i = 0; i < width; i++ ) {
    for ( j = 0; j < height; j++ ) {
      mvaddch(j,i, data[j][i]);
    }
  }
}

bool Level::collides_with(Pos position) {
  int i, j;
  bool collision = false;
  for ( i = 0; i <= 1; i++ ) {
    for ( j = 0; j <= 1; j++ ) {
      if ( level.data[position.y + i][position.x + j] != ' ' ) {
        collision = true;
      }
    }
  }
  return collision;
}


Pos::Pos() {
  x = 0;
  y = 0;
}

Pos::Pos(int i, int j) {
  x = i;
  y = j;
}

class Player {
  public:
  Pos position;
  Pos old_position;
  Player(int i, int j);
  void drawPlayer();
};

Player::Player(int i, int j) {
  position = Pos(i, j);
  old_position = Pos(i, j);
}

Player player = Player(20, 20);

void Player::drawPlayer() {
  int i;
  int j;
  for ( i = 0; i <= 1; i++ ) {
    for ( j = 0; j <= 1; j++ ) {
      mvaddch(old_position.y + j, old_position.x + i, ' ');
      mvaddch(position.y + j, position.x + i, 'P');
    }
  }
  refresh();
}

static void finish(int sig);

uint64_t frame_start;

void setup() {

  signal(SIGINT, finish);

  initscr();
  cbreak();
  curs_set(0);
  keypad(stdscr, 1);
  nodelay(stdscr,1);

  frame_start =  clock_gettime_nsec_np(CLOCK_MONOTONIC) / 1000;
}

void loop() {
  level.drawLevel();
  player.drawPlayer();

  int c = getch();

  Pos player_position_new = player.position;
  if ( c == KEY_LEFT ) {
    player_position_new.x -= 1;
  } else if ( c == KEY_RIGHT ) {
    player_position_new.x += 1;
  } else if ( c == KEY_UP ) {
    player_position_new.y -= 1;
  } else if ( c == KEY_DOWN ) {
    player_position_new.y += 1;
  }

  if ( ! level.collides_with(player_position_new) ) {
    player.old_position = player.position;
    player.position = player_position_new;
  }
}

const int FRAMES_PER_SECOND = 60;
const float MILL_PER_FRAME = 1000.0f / FRAMES_PER_SECOND;
const uint64_t MICRO_PER_FRAME =  MILL_PER_FRAME * 1000;

int main() {
    setup();
    for ( ;; ) {
      loop();

      uint64_t now =  clock_gettime_nsec_np(CLOCK_MONOTONIC) / 1000;
      uint64_t frame_length =  now - frame_start;
      uint64_t frame_left =  MICRO_PER_FRAME - frame_length;

      usleep(frame_left);
      frame_start = clock_gettime_nsec_np(CLOCK_MONOTONIC) / 1000;

    }
    finish(0);
}

static void finish(int sig) {
  endwin();
  exit(sig);
}

