#include "headers.h"
#include <curses.h>


Player::Player(int i, int j) {
  position = Pos(i, j);
  old_position = Pos(i, j);
}


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

Player::Player(){}

void Player::rotateAroundDoor(Pos center) {
  Pos relPos = position - center;
  Pos newRelPos = Pos(relPos.y, relPos.x);

  if ( relPos.x > 0 ) {
    if (relPos.y > 0 ) {
      // quatdrant 1
      // flip the y sign
      newRelPos.x = -1 * newRelPos.x;
    } else {
      newRelPos.y = -1 * newRelPos.y;
    }
  } else if ( relPos.x < 0 ) {
    if ( relPos.y < 0 ) {
      newRelPos.x = -1 * newRelPos.x;
    } else {
      newRelPos.y = -1 * newRelPos.y;
    }
  }

  position = center + newRelPos;
}

void Player::move(Level level, Door doors[]) {
  int c = getch();

  Pos player_position_new = position;
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
  int i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    if ( doors[i].collides_with(player_position_new, PLAYER_SIZE) ) {
      collides_with_door = true;
    }
  }

  if ( ! collides_with_level && ! collides_with_door ) {
    old_position = position;
    position = player_position_new;
  }

  if ( collides_with_door ) {
    // give each door a chance to rotate.
    for ( i = 0; i < NUM_DOORS; i++ ) {
      doors[i].check_and_rotate();
    }
  }
}
