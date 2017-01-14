#include "headers.h"
#include <curses.h>
#include <time.h>

Monster monsters[NUM_MONSTERS] = { Monster(13,7) };

Monster::Monster() {}

Monster::Monster(int x, int y) {
  position = Pos(x, y);
  old_position = position;
}

void Monster::draw() {
  int i, j;
  for ( i = 0; i < MONSTER_WIDTH; i++ ) {
    for ( j = 0; j < MONSTER_HEIGHT; j++ ) {

      // TODO only do ths when actually taking a step.
      mvaddch(old_position.y + j, old_position.x + i, ' ');

      mvaddch(position.y + j, position.x + i, 'M');
    }
  }
}

const int MOVES_PER_SECOND = 3;
const unsigned long NANOS_PER_MOVE = ( 1000 * 1000 * 1000 ) / 3;

timespec monster_frame_start;

void Monster::move() {

  timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);

  timespec duration = { now.tv_sec - monster_frame_start.tv_sec, now.tv_nsec - monster_frame_start.tv_nsec};
  unsigned long duration_nanos = duration.tv_sec * ( 10^9 ) + duration.tv_nsec;

  if ( duration_nanos > NANOS_PER_MOVE) {
    // move

    Pos new_position = position + Pos(1, 0);

    if ( ! level.collides_with(position, 2, 2) ) {
      old_position = position;
      position = new_position;
    }

    monster_frame_start = now;
  }
}

bool Monster::collides_with(Pos p, int w, int h) {
  return collision(p, w, h, position, MONSTER_WIDTH, MONSTER_HEIGHT);
}
