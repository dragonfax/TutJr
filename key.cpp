#include "headers.h"

const byte KEY_FRAME_SIZE = 8;

static const byte PROGMEM key_frame[] = { 
  B00000000,
  B00000000,
  B00000110,
  B11111001,
  B01010110,
  B11010000,
  B00000000,
  B00000000,
};

static const char KEYS_X = 122;
static const char KEYS_Y = 50;

const ScreenPos KEY_SIZE = ScreenPos(MONSTER_WIDTH, MONSTER_HEIGHT);

void keys_draw() {
  for ( byte i = 0; i < level.num_keys; i++ ) {
    level.keys[i].draw();
  }
  for ( byte i = 0; i < player.keys; i++ ) {
    arduboy.drawBitmap(KEYS_X, KEYS_Y + 10 * i, key_frame, MONSTER_WIDTH, MONSTER_HEIGHT, WHITE);
  }
}

void Key::draw() {
    if ( ! taken  ) {
        arduboy.drawBitmap(position.x, position.y, key_frame, MONSTER_WIDTH, MONSTER_HEIGHT, WHITE);
    }
}

bool Key::collides_with(ScreenPos position, ScreenPos size) {
    return collision(position, size, this->position, KEY_SIZE);
}

static bool Key::check_any_collides(ScreenPos pos, ScreenPos size) {
    for ( byte i = 0; i < level.num_keys; i++ ) {
        if ( ! level.keys[i].taken && level.keys[i].collides_with(pos,size) ) {
            level.keys[i].taken = true;
            player.keys++;
        }
    }
}