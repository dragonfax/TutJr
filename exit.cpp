#include "headers.h"

// and Exit is 2,2 sized, so the player can crawl into it.

    Exit::Exit() {}
    
    Exit::Exit(byte cell_x, byte cell_y) {
      position = cell_to_screen(Pos(cell_x, cell_y));
    }
    
    bool Exit::collides_with(Pos p, byte w, byte h){
      return collision(position, 2 * CELL, 2 * CELL, p, w, h);
    }
    
    void Exit::draw() {
      arduboy.fillCircle(position.x + CELL, position.y + CELL, CELL, WHITE);
    }

