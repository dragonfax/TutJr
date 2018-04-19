#include "headers.h"

const byte HEART_FRAME_SIZE = 8;

static const byte PROGMEM heart_frame[] = { 
  B00000000,
  B00001100,
  B00011110,
  B00111100,
  B00011110,
  B00001100,
  B00000000,
  B00000000,
};

static const char LIVES_X = 122;
static const char LIVES_Y = 5;

void lives_draw() {

  for ( byte i = 0; i < player.lives; i++ ) {
    arduboy.drawBitmap(LIVES_X, LIVES_Y + 10 * i, heart_frame, MONSTER_WIDTH, MONSTER_HEIGHT, WHITE);
  }
}
