#include "headers.h"

const byte MONSTER_ANIM_FRAMES = 4;
const byte MONSTER_ANIM_FRAME_SIZE = 8;

static const byte PROGMEM mon[] = { 
  B11100010,
  B10001110,
  B01111000,
  B00101100,
  B00111010,
  B10010010,
  B10010100,
  B01100100,


  B11000000,
  B10001110,
  B10001000,
  B01111000,
  B00101110,
  B00111010,
  B10010010,
  B01110011,


  B10000000,
  B10000111,
  B10000100,
  B01111100,
  B00010110,
  B00011110,
  B10010010,
  B01110011,


  B11000001,
  B10000111,
  B11111100,
  B00010110,
  B00011110,
  B00010010,
  B10010100,
  B01110110,


};

const byte NUM_MONSTERS = 5;
Monster monsters[] = { Monster(13,7), Monster(10, 1), Monster(16, 10), Monster(22,13), Monster(10, 13) };

Monster::Monster() {}

Monster::Monster(byte cell_x, byte cell_y) {
  position = cell_to_screen(Pos(cell_x, cell_y));
  old_position = position;
}

void Monster::draw() {
  arduboy.drawBitmap(position.x, position.y, &mon[anim_frame * MONSTER_ANIM_FRAME_SIZE], MONSTER_WIDTH, MONSTER_HEIGHT, WHITE);
}

const byte MOVES_PER_SECOND = 10;
const uint FRAMES_PER_MOVE = 60 / MOVES_PER_SECOND;

const Pos MONSTER_MOVES[] = { Pos(0,-1), Pos(-1,0), Pos(1,0), Pos(0,1) };

void Monster::move() {

  if ( arduboy.everyXFrames(FRAMES_PER_MOVE) ) {
    // move

    // try last direction first
    byte direction = last_direction;

    byte tries;
    for ( tries = 0 ; tries < 4; tries++) {

      Pos new_position = position + MONSTER_MOVES[direction];

      bool collides_with_door = false;
      byte i;
      for ( i = 0; i < NUM_DOORS; i++ ) {
        if ( doors[i].collides_with(new_position, MONSTER_WIDTH, MONSTER_HEIGHT) ) {
          collides_with_door = true;
        }
      }
    
      if ( ! level.collides_with(new_position, MONSTER_WIDTH, MONSTER_HEIGHT) && ! collides_with_door  ) {
        old_position = position;
        position = new_position;
        anim_frame = ( anim_frame + 1 ) % MONSTER_ANIM_FRAMES;
        last_direction = direction;

        if ( collision(player.position, PLAYER_WIDTH, PLAYER_HEIGHT, position, MONSTER_WIDTH, MONSTER_HEIGHT) ) {
          end("You Lose");
        }
        
        break;
      }

      direction = random(0,4);
    }
  }
}

bool Monster::collides_with(Pos p, byte w, byte h) {
  return collision(p, w, h, position, MONSTER_WIDTH, MONSTER_HEIGHT);
}
