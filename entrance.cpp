#include "headers.h"

Entrance::Entrance(){}

Entrance::Entrance(MapPos position) {
  this->position = cell_to_screen(position);
}