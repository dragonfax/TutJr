#include "headers.h"

Door::Door(byte cell_x, byte cell_y, byte ds) {
  center = cell_to_screen(Pos(cell_x, cell_y));
  doors = ds;
  collidedDoors = 0;
}

bool Door::collides_with_pivot(Pos position, byte w, byte h) {
  if ( collision(position, w, h, center, WALL, WALL) ) {
    return true;
  }
  return false;
}

bool Door::collides_with(Pos position, byte w, byte h) {

  collidedDoors = 0;

  if ( collision(position, w, h, center, WALL, WALL) ) {
    return true;
  }

  // doors segments are 2 squares by 1 square

  // how to check the other door segments. including rotation.
  if ( doors & DOOR_UP )  {
    if ( collision(position, w, h, center + cell_to_screen(Pos(0, -2)), WALL, CELL) ) {
      collidedDoors |= DOOR_UP;
      return true;
    }
  }

  if ( doors & DOOR_DOWN )  {
    if ( collision(position, w, h, center + cell_to_screen(Pos(0, 1)), WALL, CELL) ) {
      collidedDoors |= DOOR_DOWN;
      return true;
    }
  }

  if ( doors & DOOR_LEFT )  {
    if ( collision(position, w, h, center + cell_to_screen(Pos(-2, 0)), CELL, WALL) ) {
      collidedDoors |= DOOR_LEFT;
      return true;
    }
  }
   
  if ( doors & DOOR_RIGHT )  {
    if ( collision(position, w, h, center + cell_to_screen(Pos(1, 0)), CELL, WALL) ) {
      collidedDoors |= DOOR_RIGHT;
      return true;
    }
  }
   
  return false;
}

void Door::draw() {

    arduboy.fillRect(center.x + 1, center.y + 1, WALL, WALL, 1);



  // how to draw each segment to the rotation.

  if ( doors & DOOR_UP ) {

    arduboy.drawFastVLine( center.x + 1, center.y - CELL, CELL , 1);
    arduboy.drawFastVLine( center.x + 2, center.y - CELL, CELL , 1);

  }

  if ( doors & DOOR_DOWN ) {
 
    arduboy.drawFastVLine( center.x + 1, center.y + WALL, CELL, 1);
    arduboy.drawFastVLine( center.x + 2, center.y + WALL, CELL, 1);

  }

  if ( doors & DOOR_LEFT ) {

    arduboy.drawFastHLine( center.x - CELL, center.y + 1, CELL, 1);
    arduboy.drawFastHLine( center.x - CELL, center.y + 2, CELL, 1);

  }

  if ( doors & DOOR_RIGHT ) {

    arduboy.drawFastHLine( center.x + WALL, center.y + 1, CELL, 1);
    arduboy.drawFastHLine( center.x + WALL, center.y + 2, CELL, 1);

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
    if ( enclosure(center + cell_to_screen(Pos(-1, -2)), WALL,  CELL, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      // upper left
      rotateClockwise = true;
    }
    else if ( enclosure(center + cell_to_screen(Pos(1, -2)), WALL, CELL, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateCounter = true;
    }
  }

  if ( collidedDoors & DOOR_DOWN ) {
    if ( enclosure(center + cell_to_screen(Pos(1, 1)), WALL, CELL, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateClockwise = true;
    }
    else if ( enclosure(center + cell_to_screen(Pos(-1, 1)), WALL, CELL, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateCounter = true;
    }
  }

  if ( collidedDoors & DOOR_LEFT ) {
    if ( enclosure(center + cell_to_screen(Pos(-2, -1)), CELL, WALL, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateCounter = true;
    }
    else if ( enclosure(center + cell_to_screen(Pos(-2, 1)), CELL, WALL, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateClockwise = true;
    }
  }

  if ( collidedDoors & DOOR_RIGHT ) {
    if ( enclosure(center + cell_to_screen(Pos(1, 1)), CELL, WALL, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateCounter = true;
    }
    else if ( enclosure(center + cell_to_screen(Pos(1, -1)), CELL, WALL, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
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

Pos Door::rotatePos(Pos position) {

  // positions are normalized to cell coords. the rotation is done there.

  Pos relPos = screen_to_cell(position) - screen_to_cell(center);

  Pos newRelPos;

  if ( relPos == Pos(1,-2) ) {
    newRelPos = Pos(1, 1);
  } else if ( relPos == Pos(1, 1) ) {
    newRelPos = Pos(-2, 1);
  } else if ( relPos == Pos(-2, 1) ) {
    newRelPos = Pos(-2, -2);
  } else if ( relPos == Pos(-2, -2) ) {
    newRelPos = Pos(1, -2);
  } else {
    // unknown situation. just ignore it.
  }

  return center + cell_to_screen(newRelPos);
}

static bool Door::doors_collides_with_pivot(Pos position, byte w, byte h) {
  byte i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    if ( level_doors[i].collides_with_pivot(position, w, h) ) {
      return true;
    }
  }
  return false;
}