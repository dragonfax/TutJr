#include "headers.h"

// and Exit is 2,2 sized, so the player can crawl into it.

    Exit::Exit() {}
    
    Exit::Exit(MapPos pos) {
      position = cell_to_screen(pos);
    }
    
    bool Exit::collides_with(ScreenPos p, ScreenPos size){
      return collision(position, ScreenPos(SPACE_SIZE, SPACE_SIZE), p, size);
    }

    ScreenPos Exit::get_position() {
      return position;
    }
    
    void Exit::draw() {
      drawString(position.x + 1, position.y, "E");
    }

