#include "headers.h"

SafeSpot::SafeSpot() {}

SafeSpot::SafeSpot( byte cell_x, byte cell_y)  {
    position = cell_to_screen(Pos(cell_x, cell_y));
}

bool SafeSpot::collides_with(Pos p, byte w, byte h) {
    return collision(position, CELL, CELL, p, w, h);
}