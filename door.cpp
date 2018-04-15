#include "headers.h"

Door::Door(MapPos pos, Direction d) {
  direction = d;
  center = cell_to_screen(pos);
}

bool Door::collides_with_pivot(ScreenPos position, ScreenPos size) {
  if ( collision(position, size, center, ScreenPos(WALL_THICK, WALL_THICK)) ) {
    return true;
  }
  return false;
}

bool Door::collides_with(ScreenPos position, ScreenPos size) {

  if ( collides_with_pivot(position, size) ) {
    return true;
  }

  if ( direction == VERTICAL )  {
    if ( collision(position, size, center + cell_to_screen(MapPos(0, -2)), ScreenPos(WALL_THICK, SPACE_SIZE * 2)) ) {
      return true;
    }
  }

  if ( direction == HORIZONTAL )  {
    if ( collision(position, size, center + cell_to_screen(MapPos(-2, 0)), ScreenPos(SPACE_SIZE * 2, WALL_THICK)) ) {
      return true;
    }
  }
   
  return false;
}

void Door::draw() {

  arduboy.fillRect(center.x, center.y, WALL_THICK + 1, WALL_THICK + 1, 1);

  if ( direction == VERTICAL ) {
    arduboy.drawFastVLine( center.x + 1, center.y - SPACE_SIZE, SPACE_SIZE, 1);
    arduboy.drawFastVLine( center.x + 2, center.y - SPACE_SIZE, SPACE_SIZE, 1);
  }

  if ( direction == HORIZONTAL ) {
    arduboy.drawFastHLine( center.x - SPACE_SIZE, center.y + 1, SPACE_SIZE, 1);
    arduboy.drawFastHLine( center.x - SPACE_SIZE, center.y + 2, SPACE_SIZE, 1);
  }

}

// true for clockwise, false for counterclockwise
void Door::swing(bool direction) {
  if ( direction == HORIZONTAL ) {
    direction = VERTICAL;
  } else {
    direction = HORIZONTAL;
  }
}

/*
void Door::check_and_rotate() {

  bool rotateClockwise = false;
  bool rotateCounter = false;

  if ( collidedDoors & DOOR_UP ) {
    //check if the player collides with any cell on the left or the right of the door.
    //if so. thats where they collided from. and we rotate everything in the opposite direction.
    if ( enclosure(center + cell_to_screen(MapPos(-1, -2)), ScreenPos(CELL, 2 * CELL), player.position, ScreenPos(PLAYER_WIDTH, PLAYER_HEIGHT) ) ) {
      // upper left
      rotateClockwise = true;
    }
    else if ( enclosure(center + cell_to_screen(MapPos(1, -2)), ScreenPos(CELL, 2 * CELL), player.position, ScreenPos(PLAYER_WIDTH, PLAYER_HEIGHT) ) ) {
      rotateCounter = true;
    }
  }

  if ( collidedDoors & DOOR_DOWN ) {
    if ( enclosure(center + cell_to_screen(MapPos(1, 1)), ScreenPos(CELL, 2 * CELL), player.position, ScreenPos(PLAYER_WIDTH, PLAYER_HEIGHT) ) ) {
      rotateClockwise = true;
    }
    else if ( enclosure(center + cell_to_screen(MapPos(-1, 1)), ScreenPos(CELL, 2 * CELL), player.position, ScreenPos(PLAYER_WIDTH, PLAYER_HEIGHT) ) ) {
      rotateCounter = true;
    }
  }

  if ( collidedDoors & DOOR_LEFT ) {
    if ( enclosure(center + cell_to_screen(MapPos(-2, -1)), ScreenPos(2 * CELL, CELL), player.position, ScreenPos(PLAYER_WIDTH, PLAYER_HEIGHT) ) ) {
      rotateCounter = true;
    }
    else if ( enclosure(center + cell_to_screen(MapPos(-2, 1)), ScreenPos(2 * CELL, CELL), player.position, ScreenPos(PLAYER_WIDTH, PLAYER_HEIGHT) ) ) {
      rotateClockwise = true;
    }
  }

  if ( collidedDoors & DOOR_RIGHT ) {
    if ( enclosure(center + cell_to_screen(MapPos(1, 1)), ScreenPos(2 * CELL, CELL), player.position, ScreenPos(PLAYER_WIDTH, PLAYER_HEIGHT) ) ) {
      rotateCounter = true;
    }
    else if ( enclosure(center + cell_to_screen(MapPos(1, -1)), ScreenPos(2 * CELL, CELL), player.position, ScreenPos(PLAYER_WIDTH, PLAYER_HEIGHT) ) ) {
      rotateClockwise = true;
    }
  }

  if ( rotateClockwise) {
    swing(true);
  } else if ( rotateCounter ) {
    swing(false);
  }
}
*/

static bool Door::doors_collides_with_pivot(ScreenPos position, ScreenPos size) {
  byte i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    if ( level_doors[i].collides_with_pivot(position, size) ) {
      return true;
    }
  }
  return false;
}