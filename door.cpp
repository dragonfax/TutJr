#include "headers.h"
#include <curses.h>

Door doors[NUM_DOORS] = { Door(30, 30, true, false, true, false) };

Door::Door(int x, int y, bool u, bool d, bool l, bool r) {
  center = Pos(x, y);
  up = u;
  down = d;
  left = l;
  right = r;
}

bool Door::collides_with(Pos position, int w, int h) {

  flagUp = false;
  flagDown = false;
  flagLeft = false;
  flagRight = false;

  if ( collision(position, w, h, center, 1, 1) ) {
    return true;
  }

  // how to check the other door segments. including rotation.
  if ( up )  {
    if ( collision(position, w, h, center + Pos(0, -2), 1, 2) ) {
      flagUp = true;
      return true;
    }
  }

  if ( down )  {
    if ( collision(position, w, h, center + Pos(0, 1), 1, 2) ) {
      flagDown = true;
      return true;
    }
  }

  if ( left )  {
    if ( collision(position, w, h, center + Pos(-2, 0), 2, 1) ) {
      flagLeft = true;
      return true;
    }
  }
   
  if ( right )  {
    if ( collision(position, w, h, center + Pos(1, 0), 2, 1) ) {
      flagRight = true;
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

void Door::check_and_rotate() {

  bool rotateClockwise = false;

  if ( flagUp ) {
    /*
    check if the player collides with any cell on the left or the right of the door.
    if so. thats where they collided from. and we rotate everything in that direction.
    */
    if ( enclosure(center + Pos(-1, -2), 1, 2, player.position, PLAYER_WIDTH, PLAYER_HEIGHT ) ) {
      // upper left
      rotateClockwise = true;
    }
  }

  if ( rotateClockwise) {
    rotate(true);
    player.rotateAroundDoor(center);
  }
}


