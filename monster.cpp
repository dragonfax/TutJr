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

Monster::Monster() {}

Monster::Monster(MapPos cell) {
  position = cell_to_screen(cell);
  old_position = position;
}

void Monster::draw() {
  arduboy.drawBitmap(position.x, position.y, &mon[anim_frame * MONSTER_ANIM_FRAME_SIZE], MONSTER_WIDTH, MONSTER_HEIGHT, WHITE);
}

const byte MOVES_PER_SECOND = 10;
const uint FRAMES_PER_MOVE = 60 / MOVES_PER_SECOND;

const ScreenPos MONSTER_MOVES[] = { ScreenPos(0,-1), ScreenPos(-1,0), ScreenPos(1,0), ScreenPos(0,1) };
const ScreenPos MONSTER_SIZE = ScreenPos(MONSTER_WIDTH,MONSTER_HEIGHT);

void Monster::move() {

  if ( arduboy.everyXFrames(FRAMES_PER_MOVE) ) {
    // move

    // try last direction first
    byte direction = last_direction;

    byte tries;
    for ( tries = 0 ; tries < 4; tries++) {

      ScreenPos new_position = position + MONSTER_MOVES[direction];

      bool collides_with_safe_spot = safeSpot.collides_with(new_position, MONSTER_SIZE);

      bool collides_with_door = false;
      byte i;
      for ( i = 0; i < NUM_DOORS; i++ ) {
        if ( level_doors[i].collides_with(new_position, MONSTER_SIZE, this) ) {
          collides_with_door = true;
        }
      }

      bool collides_with_monster = Monster::collides_with_any(new_position, MONSTER_SIZE, this);

      if ( ! collides_with_safe_spot && ! level.collides_with(new_position, MONSTER_SIZE) && ! collides_with_door && ! collides_with_monster ) {
        old_position = position;
        position = new_position;
        anim_frame = ( anim_frame + 1 ) % MONSTER_ANIM_FRAMES;
        last_direction = direction;

        if ( collision(player.position, PLAYER_SIZE, position, MONSTER_SIZE) ) {
          end("You Lose");
        }
        
        break;
      }

      direction = random(0,4);
    }
  }
}

ScreenPos Monster::get_position() {
  return position;
}

bool Monster::collides_with(ScreenPos p, ScreenPos size, Entity* entity) {
  if ( entity == this ) {
    return false;
  }
  return collision(p, size, position, MONSTER_SIZE);
}

bool Monster::operator== ( Monster & rhs ) {
  return this == &rhs;
}

static bool Monster::collides_with_any(ScreenPos position, ScreenPos size, Entity* entity) {
  for ( byte i = 0; i < NUM_MONSTERS; i++ ) {
    if ( monsters[i].collides_with(position, size, entity) ) {
      return true;
    }
  }
  return false;
}
  