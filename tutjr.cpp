
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "headers.h"

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

bool Level::collides_with(Pos position, int size) {
  int i, j;
  bool collision = false;
  for ( i = 0; i < size; i++ ) {
    for ( j = 0; j < size; j++ ) {
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

bool Pos::operator==(const Pos &other ) {
  return x == other.x && y == other.y ;
}

Pos Pos::operator+(const Pos &other ) {
  return Pos(x + other.x, y + other.y);
}

Pos Pos::operator-(const Pos &other) {
  return Pos(x - other.x, y - other.y);
}

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

void Player::rotateAroundDoor(Pos center) {
  Pos relPos = position - center;
  Pos newRelPos = Pos(relPos.y, relPos.x);

  if ( relPos.x > 0 ) {
    if (relPos.y > 0 ) {
      // quatdrant 1
      // flip the y sign
      newRelPos.y = -1 * newRelPos.y;
    } else {
      newRelPos.x = -1 * newRelPos.x;
    }
  } else if ( relPos.x < 0 ) {
    if ( relPos.y < 0 ) {
      newRelPos.y = -1 * newRelPos.y;
    } else {
      newRelPos.x = -1 * newRelPos.y;
    }
  }
}


Door::Door(int x, int y, bool u, bool d, bool l, bool r) {
  center = Pos(x, y);
  up = u;
  down = d;
  left = l;
  right = r;
}

bool collision(Pos p1, int s1, Pos p2, int s2) {

  int i1;
  int j1;
  for ( i1 = 0; i1 < s1; i1++ ) {
    for ( j1 = 0; j1 < s1; j1++ ) {
      int i2;
      int j2;
      for ( i2 = 0; i2 < s2; i2++ ) {
        for ( j2 = 0; j2 < s2; j2++ ) {
          Pos np1 = p1 + Pos(i1, j1);
          Pos np2 = p2 + Pos(i2, j2);
          if ( np1 == np2 ) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

bool Door::collides_with(Pos position, int size) {

  if ( collision(position, size, center, 1) ) {
    return true;
  }

  // doors are the only thing that is 2x1, so we give them special handling for collision.
  // rather than expand the collision system to arbitrary shapes.

  // how to check the other door segments. including rotation.
  if ( up )  {
    if ( collision(position, size, center + Pos(0, -1), 1) ) {
      return true;
    }
    if ( collision(position, size, center + Pos(0, -2), 1) ) {
      return true;
    }
  }

  if ( down )  {
    if ( collision(position, size, center + Pos(0, 1), 1) ) {
      return true;
    }
    if ( collision(position, size, center + Pos(0, 2), 1) ) {
      return true;
    }
  }

  if ( left )  {
    if ( collision(position, size, center + Pos(-1, 0), 1) ) {
      return true;
    }
    if ( collision(position, size, center + Pos(-2, 0), 1) ) {
      return true;
    }
  }
   
  if ( right )  {
    if ( collision(position, size, center + Pos(1, 0), 1) ) {
      return true;
    }
    if ( collision(position, size, center + Pos(2, 0), 1) ) {
      return true;
    }
  }
   
  return false;
}

void Door::draw() {
  mvaddch(center.y, center.x, 'C');

  // how to draw each segment to the rotation.

  if ( up ) {
    mvaddch(center.y - 1, center.x, 'D');
    mvaddch(center.y - 2, center.x, 'D');
  }

  if ( down ) {
    mvaddch(center.y + 1, center.x, 'D');
    mvaddch(center.y + 2, center.x, 'D');
  }

  if ( left ) {
    mvaddch(center.y, center.x - 1, 'D');
    mvaddch(center.y, center.x - 2, 'D');
  }

  if ( right ) {
    mvaddch(center.y, center.x + 1, 'D');
    mvaddch(center.y, center.x + 2, 'D');
  }
}

// true for clockwise, false for counterclockwise
void Door::rotate(bool direction) {
  bool u, d, l, r = false;

  if (direction) {
    if(up) {
      r = true;
    }
    if(right) {
      d = true;
    }
    if(down) {
      l = true;
    }
    if ( left) {
      u = true;
    }
  } else {
    if(up) {
      l = true;
    }
    if(right) {
      u = true;
    }
    if ( down) {
      r = true;
    }
    if ( left) {
      d = true;
    }
  }

  up = u;
  down = d;
  left = l;
  right = r;
}

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

  int i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    doors[i].draw();
  }

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
  } else if ( c == 'q' ) {
    finish(0);
  }

  bool collides_with_level = level.collides_with(player_position_new, PLAYER_SIZE);
  bool collides_with_door = false;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    collides_with_door = doors[i].collides_with(player_position_new, PLAYER_SIZE);
  }

  if ( ! collides_with_level && ! collides_with_door ) {
    player.old_position = player.position;
    player.position = player_position_new;
  }
}

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

