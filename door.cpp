#include "headers.h"

Door::Door(MapPos pos, byte ds) {
  center = cell_to_screen(pos);
  doors = ds;
  collidedDoors = 0;
}

bool Door::collides_with_pivot(ScreenPos position, ScreenPos size) {
  if ( collision(position, size, center, ScreenPos(WALL_THICK, WALL_THICK)) ) {
    return true;
  }
  return false;
}

bool Door::collides_with(ScreenPos position, ScreenPos size) {

  collidedDoors = 0;

  if ( collides_with_pivot(position, size) ) {
    return true;
  }

  // doors segments are 2 squares by 1 square

  // how to check the other door segments. including rotation.
  if ( doors & DOOR_UP )  {
    if ( collision(position, size, center + cell_to_screen(MapPos(0, -2)), ScreenPos(WALL_THICK, SPACE_SIZE)) ) {
      collidedDoors |= DOOR_UP;
      return true;
    }
  }

  if ( doors & DOOR_DOWN )  {
    if ( collision(position, size, center + cell_to_screen(MapPos(0, 1)), ScreenPos(WALL_THICK, SPACE_SIZE)) ) {
      collidedDoors |= DOOR_DOWN;
      return true;
    }
  }

  if ( doors & DOOR_LEFT )  {
    if ( collision(position, size, center + cell_to_screen(MapPos(-2, 0)), ScreenPos(SPACE_SIZE, WALL_THICK)) ) {
      collidedDoors |= DOOR_LEFT;
      return true;
    }
  }
   
  if ( doors & DOOR_RIGHT )  {
    if ( collision(position, size, center + cell_to_screen(MapPos(1, 0)), ScreenPos(SPACE_SIZE, WALL_THICK)) ) {
      collidedDoors |= DOOR_RIGHT;
      return true;
    }
  }
   
  return false;
}

void Door::draw() {

    arduboy.fillRect(center.x, center.y, WALL_THICK + 1, WALL_THICK + 1, 1);



  // how to draw each segment to the rotation.

  if ( doors & DOOR_UP ) {

    arduboy.drawFastVLine( center.x + 1, center.y - 2 * CELL, CELL * 2, 1);
    arduboy.drawFastVLine( center.x + 2, center.y - 2 * CELL, CELL * 2, 1);

  }

  if ( doors & DOOR_DOWN ) {
 
    arduboy.drawFastVLine( center.x + 1, center.y + CELL, CELL * 2, 1);
    arduboy.drawFastVLine( center.x + 2, center.y + CELL, CELL * 2, 1);

  }

  if ( doors & DOOR_LEFT ) {

    arduboy.drawFastHLine( center.x - 2 * CELL, center.y + 1, CELL * 2, 1);
    arduboy.drawFastHLine( center.x - 2 * CELL, center.y + 2, CELL * 2, 1);

  }

  if ( doors & DOOR_RIGHT ) {

    arduboy.drawFastHLine( center.x + CELL, center.y + 1, CELL * 2, 1);
    arduboy.drawFastHLine( center.x + CELL, center.y + 2, CELL * 2, 1);

  }
}

byte fourBitShiftLeft(byte i) {
  return ((i << 1) & 15) | (i >> 3);
}

byte fourBitShiftRight(byte i) {
  return (i >> 1) | ((i << 3) & 15);
}

// true for clockwise, false for counterclockwise
void Door::swing(bool direction) {
  if ( direction ) {
    doors = fourBitShiftLeft(doors);
  } else {
    doors = fourBitShiftRight(doors);
  }
}

void Door::check_and_rotate() {

  bool rotateClockwise = false;
  bool rotateCounter = false;

  if ( collidedDoors & DOOR_UP ) {
    /*
    check if the player collides with any cell on the left or the right of the door.
    if so. thats where they collided from. and we rotate everything in the opposite direction.
    */
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
    // TODO rotate player only if necessary.
    // player.position = rotatePos(player.position);
  } else if ( rotateCounter ) {
    swing(false);
    // player.position = rotatePos(player.position);
    // player.position = rotatePos(player.position);
    // player.position = rotatePos(player.position);
  }
}

ScreenPos Door::rotatePos(ScreenPos position) {

  // positions are normalized to cell coords. the rotation is done there.

  MapPos relPos = screen_to_cell(position) - screen_to_cell(center);

  MapPos newRelPos;

  if ( relPos == MapPos(1,-2) ) {
    newRelPos = MapPos(1, 1);
  } else if ( relPos == MapPos(1, 1) ) {
    newRelPos = MapPos(-2, 1);
  } else if ( relPos == MapPos(-2, 1) ) {
    newRelPos = MapPos(-2, -2);
  } else if ( relPos == MapPos(-2, -2) ) {
    newRelPos = MapPos(1, -2);
  } else {
    // unknown situation. just ignore it.
  }

  return center + cell_to_screen(newRelPos);
}

static bool Door::doors_collides_with_pivot(ScreenPos position, ScreenPos size) {
  byte i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    if ( level_doors[i].collides_with_pivot(position, size) ) {
      return true;
    }
  }
  return false;
}