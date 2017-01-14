#include "headers.h"

static const unsigned char PROGMEM hero[] = { 
  B00111000,
  B00111000,
  B11111110,
  B10111010,
  B10101010,
  B00101000,
  B00101000,
  B00101000
  };

Player::Player(int i, int j) {
  position = Pos(i, j);
  old_position = Pos(i, j);
}

void Player::drawPlayer() {

      // mvaddch(old_position.y + j, old_position.x + i, ' ');
      // mvaddch(position.x * CELL_SIZE, position.y * CELL_SIZE, 'P');
      arduboy.drawBitmap(position.x * CELL_SIZE, position.y * CELL_SIZE, hero, 8, 8, 1);

}

Player::Player(){}

void Player::rotateAroundDoor(Pos center) {
  Pos relPos = position - center;

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
    // known situation. just ignore it.
  }

  position = center + newRelPos;
}

void Player::move(Level level, Door doors[]) {

  if ( ! arduboy.everyXFrames(5) )
    return;

  Pos player_position_new = position;
  if ( arduboy.pressed(LEFT_BUTTON) ) {
    player_position_new.x -= 1;
  } else if ( arduboy.pressed(RIGHT_BUTTON) ) {
    player_position_new.x += 1;
  } else if ( arduboy.pressed(UP_BUTTON) ) {
    player_position_new.y -= 1;
  } else if ( arduboy.pressed(DOWN_BUTTON) ) {
    player_position_new.y += 1;
  }

  bool collides_with_level = level.collides_with(player_position_new, PLAYER_WIDTH, PLAYER_HEIGHT);
  bool collides_with_door = false;
  int i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    if ( doors[i].collides_with(player_position_new, PLAYER_WIDTH, PLAYER_HEIGHT) ) {
      collides_with_door = true;
    }
  }

  bool collides_with_monster = false;
  for ( i = 0; i < NUM_MONSTERS; i++ ) {
    if ( monsters[i].collides_with(player_position_new, PLAYER_WIDTH, PLAYER_HEIGHT) ) {
      collides_with_monster = true;
    }
  }

  if ( ! collides_with_level && ! collides_with_door && ! collides_with_monster) {
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
