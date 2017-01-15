#include "headers.h"


void drawString(byte x, byte y, const char* str);
void end(const char *str) ;


Player player = Player(1, 1);

const byte PLAYER_ANIM_FRAMES = 4;
const byte PLAYER_ANIM_FRAME_SIZE = 8;

const byte PLAYER_ANIM_DOWN = 0;
const byte PLAYER_ANIM_RIGHT = PLAYER_ANIM_FRAMES * PLAYER_ANIM_FRAME_SIZE;


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

Player::Player(byte cell_x, byte cell_y) {
  position = cell_to_screen(Pos(cell_x, cell_y));
  old_position = position;
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


void Player::move() {

  if ( ! arduboy.everyXFrames(2) )
    return;

  Pos player_position_new = position;
  if ( arduboy.pressed(LEFT_BUTTON) ) {
    player_position_new.x -= 1;
    player.direction = DIR_LEFT;
  } else if ( arduboy.pressed(RIGHT_BUTTON) ) {
    player_position_new.x += 1;
    player.direction = DIR_RIGHT;
  } else if ( arduboy.pressed(UP_BUTTON) ) {
    player_position_new.y -= 1;
    player.direction = DIR_UP;
  } else if ( arduboy.pressed(DOWN_BUTTON) ) {
    player_position_new.y += 1;
    player.direction = DIR_DOWN;
  }

  if ( ! ( player_position_new == position ) ) {
  
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
  
      if ( arduboy.everyXFrames(10) ) {
      player.anim_frame = ( player.anim_frame + 1 ) % PLAYER_ANIM_FRAMES;
      }
    }

    if ( collides_with_monster ) {
      end("You Lose");
    }
  
    if ( collides_with_door ) {
      // give each door a chance to rotate.
      for ( i = 0; i < NUM_DOORS; i++ ) {
        doors[i].check_and_rotate();
      }
    }

    if ( exitSpace.collides_with(position, PLAYER_WIDTH, PLAYER_HEIGHT) ) {
      end("You Win!");

    }

  }
}

void end(const char *str) {
  arduboy.clear();
  drawString(10, 10, str);
  arduboy.display();
  delay( 3 * 1000);
  exit(0);
}
      
void drawString(byte x, byte y, const char* str){
  byte offset;
  byte i;
  for ( i = 0; i < strlen(str); i++ ) {
    arduboy.drawChar(x + offset, y, str[i], WHITE, BLACK, 1);
    offset += 8;
  }
}

