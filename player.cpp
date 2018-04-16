#include "headers.h"




const byte PLAYER_ANIM_FRAMES = 4;
const byte PLAYER_ANIM_FRAME_SIZE = 8;

const byte PLAYER_ANIM_DOWN = 0;
const byte PLAYER_ANIM_RIGHT = PLAYER_ANIM_FRAMES * PLAYER_ANIM_FRAME_SIZE;

const byte MOVE_STEPS = 1;


static const byte PROGMEM hero[] = { 

  // moving down animation
  B00010000,
  B00001000,
  B11111010,
  B00011111,
  B00011111,
  B01111010,
  B00001000,
  B00110000,

  B00110000,
  B00001000,
  B11111010,
  B00011111,
  B00011111,
  B11111010,
  B00001000,
  B00110000,

  B00110000,
  B00001000,
  B01111010,
  B00011111,
  B00011111,
  B11111010,
  B00001000,
  B00010000,

  B00110000,
  B00001000,
  B11111010,
  B00011111,
  B00011111,
  B11111010,
  B00001000,
  B00110000,

  // moving right, animation

  B00000000,
  B00000000,
  B01111000,
  B01111111,
  B11111111,
  B10011010,
  B00001000,
  B00000000,

  B00000000,
  B00000000,
  B11111000,
  B10111111,
  B01111111,
  B01011010,
  B00001000,
  B00000000,


  B00000000,
  B11100000,
  B10111000,
  B00111111,
  B00111111,
  B01111010,
  B01001000,
  B00000000,

  B00000000,
  B01100000,
  B01111000,
  B00111111,
  B00111111,
  B11011010,
  B10001000,
  B00000000,

};

Player::Player(MapPos cell) {
  position = cell_to_screen(cell);
  old_position = position;
  moveSteps = 0;
}


const byte DIR_LEFT = 1;
const byte DIR_RIGHT = 2;
const byte DIR_UP = 3;
const byte DIR_DOWN = 4;

void Player::draw() {
  byte animation;

  if (player.direction == DIR_LEFT || player.direction == DIR_RIGHT ) {
    animation = PLAYER_ANIM_RIGHT;
  } else {
    animation = PLAYER_ANIM_DOWN;
  }
  arduboy.drawBitmap(position.x, position.y, &hero[animation  + player.anim_frame * PLAYER_ANIM_FRAME_SIZE], PLAYER_WIDTH, PLAYER_HEIGHT, 1);
}

Player::Player(){}

ScreenPos Player::get_position() {
  return position;
}

void Player::move() {

  if ( ! arduboy.everyXFrames(2) )
    return;

  if ( moveSteps == 0 ) {
    // not moving, take a new movement command

    if ( arduboy.pressed(LEFT_BUTTON) ) {
      if ( canMoveTo(ScreenPos(position.x - 1, position.y)) ) {
        player.moveSteps = MOVE_STEPS;
        player.direction = DIR_LEFT;
      }
    }

    if ( arduboy.pressed(RIGHT_BUTTON) ) {
      if ( canMoveTo(ScreenPos(position.x + 1, position.y)) ) {
        player.moveSteps = MOVE_STEPS;
        player.direction = DIR_RIGHT;
      }
    }

    if ( arduboy.pressed(UP_BUTTON) ) {
      if ( canMoveTo(ScreenPos(position.x, position.y - 1)) ) {
        player.direction = DIR_UP;
        player.moveSteps = MOVE_STEPS;
      }
    }

    if ( arduboy.pressed(DOWN_BUTTON) ) {
      if ( canMoveTo(ScreenPos(position.x, position.y + 1)) ) {
        player.direction = DIR_DOWN;
        player.moveSteps = MOVE_STEPS;
      }
    }
      
  }

  if ( moveSteps > 0 ) {
    // move one step

    if ( direction == DIR_LEFT ) {
      moveTo(ScreenPos(position.x - 1, position.y));
      player.moveSteps -= 1;
    }

    if ( direction == DIR_RIGHT ) {
      moveTo(ScreenPos(position.x + 1, position.y));
      player.moveSteps -= 1;
    }

    if ( direction == DIR_UP ) {
      moveTo(ScreenPos(position.x, position.y - 1));
      player.moveSteps -= 1;
    }

    if ( direction == DIR_DOWN ) {
      moveTo(ScreenPos(position.x, position.y + 1));
      player.moveSteps -= 1;
    }
  }
}

bool Player::canMoveTo(ScreenPos player_position_new) {
  return ! Door::doors_collides_with_pivot(player_position_new, PLAYER_SIZE) && ! level.collides_with(player_position_new, PLAYER_SIZE);
}

void Player::moveTo(ScreenPos player_position_new) {

  if ( ! ( player_position_new == position ) ) {

    bool collides_with_level = level.collides_with(player_position_new, PLAYER_SIZE);
 
    bool collides_with_monster = Monster::collides_with_any(player_position_new, PLAYER_SIZE, this);
 
    // give each door a chance to say "no go" or to rotaate itself.
    // but we can't commit unless we're actually moving there.
    bool collides_with_door = Door::doors_collides_with_door(player_position_new, PLAYER_SIZE, this);

    if ( ! collides_with_level && ! collides_with_monster && ! collides_with_door) {
      old_position = position;
      position = player_position_new;
  
      if ( arduboy.everyXFrames(10) ) {
        player.anim_frame = ( player.anim_frame + 1 ) % PLAYER_ANIM_FRAMES;
      }
    }

    if ( collides_with_monster ) {
      end("You Lose");
    }
 
    if ( exitSpace.collides_with(position, PLAYER_SIZE) ) {
      end("You Win!");

    }

  }
}



