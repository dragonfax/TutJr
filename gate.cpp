#include "headers.h"

const byte GATE_FRAME_SIZE = 8;

static const byte PROGMEM gate_frame[] = { 
  B11111111,
  B11111111,
  B11111001,
  B00000110,
  B10101001,
  B00101111,
  B11111111,
  B11111111,
};

const ScreenPos GATE_SIZE = ScreenPos(MONSTER_WIDTH, MONSTER_HEIGHT);

void gates_draw() {
  for ( byte i = 0; i < level.num_gates; i++ ) {
    level.gates[i].draw();
  }
}

void Gate::draw() {
    if ( ! opened  ) {
        arduboy.drawBitmap(position.x, position.y, gate_frame, MONSTER_WIDTH, MONSTER_HEIGHT, WHITE);
    }
}

bool Gate::collides_with(ScreenPos position, ScreenPos size) {
    return collision(position, size, this->position, GATE_SIZE);
}

static bool Gate::check_any_collides(ScreenPos pos, ScreenPos size) {
    for ( byte i = 0; i < level.num_gates; i++ ) {
        if ( ! level.gates[i].opened && level.gates[i].collides_with(pos,size) ) {
            if ( player.keys > 0 ) {
                player.keys--;
                level.gates[i].opened = true;
                return false;
            } else {
                return true;
            }
        }
    }
    return false;
}