#include "headers.h"

Door::Door(MapPos pos, Direction d) {
  direction = d;
  center = cell_to_screen(pos);
}

bool Door::collides_with_pivot(ScreenPos new_position, ScreenPos size) {
  if ( collision(new_position, size, center, ScreenPos(WALL_THICK, WALL_THICK)) ) {
    return true;
  }
  return false;
}

// TODO different constants for the visible door, vs the collision door.
const byte DOOR_LENGTH = SPACE_SIZE;
const byte DOOR_WIDTH = WALL_THICK;

const ScreenPos QUADRANT_SIZE = ScreenPos(DOOR_LENGTH,DOOR_LENGTH);
const ScreenPos QUADRANT_1_POS = ScreenPos(-DOOR_LENGTH,-DOOR_LENGTH);
const ScreenPos QUADRANT_2_POS = ScreenPos(1,-DOOR_LENGTH);
const ScreenPos QUADRANT_3_POS = ScreenPos(1,1);
const ScreenPos QUADRANT_4_POS = ScreenPos(-DOOR_LENGTH,1);

const ScreenPos DOOR_VERTICAL_POS = ScreenPos(0,-DOOR_LENGTH);
const ScreenPos DOOR_VERTICAL_SIZE = ScreenPos(DOOR_WIDTH, DOOR_LENGTH * 2 + DOOR_WIDTH);
const ScreenPos DOOR_HORIZONTAL_POS = ScreenPos(-DOOR_LENGTH,0);
const ScreenPos DOOR_HORIZONTAL_SIZE = ScreenPos(DOOR_LENGTH * 2 + DOOR_WIDTH, DOOR_WIDTH);

const ScreenPos PIXEL_SIZE = ScreenPos(1,1);

bool Door::collides_with(ScreenPos new_position, ScreenPos size, Entity* entity, bool canPivot) {

  if ( collides_with_pivot(new_position, size) ) {
    return true;
  }

  if ( direction == VERTICAL && collision(new_position, size, center + DOOR_VERTICAL_POS, DOOR_VERTICAL_SIZE) ) {

    if ( ! canPivot ) {
      return true;
    }

    if ( collision(entity->get_position(), PIXEL_SIZE, center + QUADRANT_2_POS, QUADRANT_SIZE) || 
      collision(entity->get_position(), PIXEL_SIZE, center + QUADRANT_4_POS, QUADRANT_SIZE) 
    ) {
      // counter clockwise

      if ( Monster::collides_with_any(center + QUADRANT_1_POS, QUADRANT_SIZE, entity) ||
        Monster::collides_with_any(center + QUADRANT_3_POS, QUADRANT_SIZE, entity)
      ) {
        // monster blocking path, can't rotate
        return true;
      }

      swing();
      return false;
    } else if ( collision(entity->get_position(), PIXEL_SIZE, center + QUADRANT_1_POS, QUADRANT_SIZE) || 
      collision(entity->get_position(), PIXEL_SIZE,center + QUADRANT_3_POS, QUADRANT_SIZE) 
    ) {
      // clockwise.

      if ( Monster::collides_with_any(center + QUADRANT_2_POS, QUADRANT_SIZE, entity) ||
        Monster::collides_with_any(center + QUADRANT_4_POS, QUADRANT_SIZE, entity)
      ) {
        return true;
      }

      swing();
      return false;
    }

    return true;
  } else if ( direction == HORIZONTAL && collision(new_position, size, center + DOOR_HORIZONTAL_POS, DOOR_HORIZONTAL_SIZE) ) {

    if ( ! canPivot ) {
      return true;
    }

    if ( collision(entity->get_position(), PIXEL_SIZE, center + QUADRANT_3_POS, QUADRANT_SIZE) || 
      collision(entity->get_position(), PIXEL_SIZE, center + QUADRANT_1_POS, QUADRANT_SIZE) 
    ) {
      if ( Monster::collides_with_any(center + QUADRANT_2_POS, QUADRANT_SIZE, entity) || 
        Monster::collides_with_any(center + QUADRANT_4_POS, QUADRANT_SIZE, entity) 
      ) {
        return true;
      }
      swing();
      return false;
    } else if ( collision(entity->get_position(), PIXEL_SIZE, center + QUADRANT_2_POS, QUADRANT_SIZE) || 
      collision(entity->get_position(), PIXEL_SIZE, center + QUADRANT_4_POS, QUADRANT_SIZE) 
    ) {
      if ( Monster::collides_with_any(center + QUADRANT_1_POS, QUADRANT_SIZE, entity) ||
        Monster::collides_with_any(center + QUADRANT_3_POS, QUADRANT_SIZE, entity) 
      ) {
        return true;
      }
      swing();
      return false;
    }

    return true;
  }
   
  return false;
}

void Door::draw() {

  arduboy.drawRect(center.x - 1, center.y - 1, 3, 3, 1);

  for ( byte i = 2*DOOR_LENGTH; i > 0; i-- ) {
    if ( isOdd(i) ) {
      if ( direction == VERTICAL ) {
        arduboy.drawPixel( center.x, center.y - DOOR_LENGTH + i, WHITE);
      } else if ( direction == HORIZONTAL ) {
        arduboy.drawPixel( center.x - DOOR_LENGTH + i, center.y, WHITE);
      }
    }
  }
}

// true for clockwise, false for counterclockwise
void Door::swing() {
  if ( direction == HORIZONTAL ) {
    direction = VERTICAL;
  } else {
    direction = HORIZONTAL;
  }
}

bool Level::doors_collides_with_door(ScreenPos new_position, ScreenPos size, Entity* entity, bool canPivot) {
  for ( byte i = 0; i < num_doors; i++ ) {
    if ( doors[i].collides_with(new_position, size, entity, canPivot) ) {
      return true;
    }
  }
  return false;
}

bool Level::doors_collides_with_pivot(ScreenPos new_position, ScreenPos size) {
  byte i;
  for ( i = 0; i < num_doors; i++ ) {
    if ( doors[i].collides_with_pivot(new_position, size) ) {
      return true;
    }
  }
  return false;
}