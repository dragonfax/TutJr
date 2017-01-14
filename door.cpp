#include "headers.h"

Door doors[NUM_DOORS] = { 
  Door(3, 12, 1) ,
  Door(9, 9, 1)
};

Door::Door(int x, int y, byte ds) {
  center = Pos(x, y);
  doors = ds;
  collidedDoors = 0;
}

bool Door::collides_with(Pos position, int w, int h) {

  collidedDoors = 0;

  if ( collision(position, w, h, center, 1, 1) ) {
    return true;
  }

  // doors segments are 2 squares by 1 square

  // how to check the other door segments. including rotation.
  if ( doors & DOOR_UP )  {
    if ( collision(position, w, h, center + Pos(0, -2), 1, 2) ) {
      collidedDoors |= DOOR_UP;
      return true;
    }
  }

  if ( doors & DOOR_DOWN )  {
    if ( collision(position, w, h, center + Pos(0, 1), 1, 2) ) {
      collidedDoors |= DOOR_DOWN;
      return true;
    }
  }

  if ( doors & DOOR_LEFT )  {
    if ( collision(position, w, h, center + Pos(-2, 0), 2, 1) ) {
      collidedDoors |= DOOR_LEFT;
      return true;
    }
  }
   
  if ( doors & DOOR_RIGHT )  {
    if ( collision(position, w, h, center + Pos(1, 0), 2, 1) ) {
      collidedDoors |= DOOR_RIGHT;
      return true;
    }
  }
   
  return false;
}

void Door::draw() {
  // mvaddch(center.y, center.x, 'C');
  // arduboy.drawRect(center.y * CELL_SIZE, center.x * CELL_SIZE, CELL_SIZE, CELL_SIZE, 1);
  arduboy.drawPixel(center.y * CELL_SIZE + 1, center.x * CELL_SIZE + 1, 1);


  // how to draw each segment to the rotation.

  if ( doors & DOOR_UP ) {
    // mvaddch(center.y - 1, center.x, 'D');
    // mvaddch(center.y - 2, center.x, 'D');
    arduboy.drawFastVLine( (center.x) * CELL_SIZE + CELL_SIZE/2, (center.y - 2)* CELL_SIZE, CELL_SIZE * 2, 1);
  }

  if ( doors & DOOR_DOWN ) {
    // mvaddch(center.y + 1, center.x, 'D');
    // mvaddch(center.y + 2, center.x, 'D');
    arduboy.drawFastVLine( (center.x) * CELL_SIZE + CELL_SIZE/2, (center.y + 1)* CELL_SIZE, CELL_SIZE * 2, 1);
  }

  if ( doors & DOOR_LEFT ) {
    // mvaddch(center.y, center.x - 1, 'D');
    // mvaddch(center.y, center.x - 2, 'D');
    arduboy.drawFastHLine( (center.x - 2) * CELL_SIZE, (center.y)* CELL_SIZE + CELL_SIZE/2, CELL_SIZE * 2, 1);
  }

  if ( doors & DOOR_RIGHT ) {
    // mvaddch(center.y, center.x + 1, 'D');
    // mvaddch(center.y, center.x + 2, 'D');
    arduboy.drawFastHLine( (center.x + 1) * CELL_SIZE, (center.y)* CELL_SIZE + CELL_SIZE/2, CELL_SIZE * 2, 1);
  }
}

byte fourBitShiftLeft(byte i) {
  return ((i << 1) & 15) | (i >> 3);
}

byte fourBitShiftRight(byte i) {
  return (i >> 1) | ((i << 3) & 15);
}

// true for clockwise, false for counterclockwise
void Door::rotate(bool direction) {
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
    if ( enclosure(center + Pos(-1, -2), 1, 2, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      // upper left
      rotateClockwise = true;
    }
    else if ( enclosure(center + Pos(1, -2), 1, 2, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateCounter = true;
    }
  }

  if ( collidedDoors & DOOR_DOWN ) {
    if ( enclosure(center + Pos(1, 1), 1, 2, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateClockwise = true;
    }
    else if ( enclosure(center + Pos(-1, 1), 1, 2, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateCounter = true;
    }
  }

  if ( collidedDoors & DOOR_LEFT ) {
    if ( enclosure(center + Pos(-2, -1), 2, 1, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateCounter = true;
    }
    else if ( enclosure(center + Pos(-2, 1), 2, 1, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateClockwise = true;
    }
  }

  if ( collidedDoors & DOOR_RIGHT ) {
    if ( enclosure(center + Pos(1, 1), 2, 1, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateCounter = true;
    }
    else if ( enclosure(center + Pos(1, -1), 2, 1, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      rotateClockwise = true;
    }
  }

  if ( rotateClockwise) {
    rotate(true);
    player.rotateAroundDoor(center);
  } else if ( rotateCounter ) {
    rotate(false);
    player.rotateAroundDoor(center);
    player.rotateAroundDoor(center);
    player.rotateAroundDoor(center);
  }
}


