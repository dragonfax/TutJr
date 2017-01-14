#include "headers.h"

Monster monsters[NUM_MONSTERS] = { Monster(13,7) };

Monster::Monster() {}

Monster::Monster(int x, int y) {
  position = Pos(x, y);
  old_position = position;
}

void Monster::draw() {
      mvaddch(position.x * CELL_SIZE, position.y * CELL_SIZE, 'M');

}

const int MOVES_PER_SECOND = 3;
const int FRAMES_PER_MOVE = 60 / MOVES_PER_SECOND;

void Monster::move() {

  if ( arduboy.everyXFrames(FRAMES_PER_MOVE) ) {
    // move

    Pos new_position = position + Pos(1, 0);

    if ( ! level.collides_with(position, 2, 2) ) {
      old_position = position;
      position = new_position;
    }

  }
}

bool Monster::collides_with(Pos p, int w, int h) {
  return collision(p, w, h, position, MONSTER_WIDTH, MONSTER_HEIGHT);
}
