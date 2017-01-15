#include "headers.h"

Player player = Player(10, 5);

const byte PLAYER_ANIM_FRAMES = 4;

const byte PLAYER_ANIM_DOWN = 0;
const byte PLAYER_ANIM_RIGHT = 4 * 8;

static const byte PROGMEM hero[] = { 

  // moving down animation
  B00011000,
  B00111100,
  B00011000,
  B01111110,
  B10111101,
  B00100101,
  B00100100,
  B00100000,

  B00011000,
  B00111100,
  B00011000,
  B01111110,
  B10111101,
  B10100101,
  B00100100,
  B00100100,

  B00011000,
  B00111100,
  B00011000,
  B01111110,
  B10111101,
  B10100100,
  B00100100,
  B00000100,

  B00011000,
  B00111100,
  B00011000,
  B01111110,
  B10111101,
  B10100101,
  B00100100,
  B00100100,

  // moving right, animation

  B00011000,
  B00011100,
  B00011000,
  B00111110,
  B00111100,
  B00111000,
  B00111000,
  B00001100,

  B00011000,
  B00011100,
  B00011000,
  B00111110,
  B00111100,
  B00111000,
  B00101100,
  B00110000,

  B00011000,
  B00011100,
  B00011000,
  B00111110,
  B00111100,
  B01111100,
  B01000110,
  B01100000,

  B00011000,
  B00011100,
  B00011000,
  B00111110,
  B00111100,
  B01111000,
  B01100100,
  B00000110,

};

Player::Player(byte cell_x, byte cell_y) {
  position = cell_to_screen(Pos(cell_x, cell_y));
  old_position = position;
}

void Player::draw() {
  arduboy.drawBitmap(position.x, position.y, hero, PLAYER_WIDTH, PLAYER_HEIGHT, 1);
}

Player::Player(){}

void Player::move() {

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
  byte i;
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
