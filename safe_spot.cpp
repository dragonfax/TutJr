#include "headers.h"

SafeSpot::SafeSpot() {}

SafeSpot::SafeSpot(MapPos cell) {
    position = cell_to_screen(cell);
}

bool SafeSpot::collides_with(ScreenPos p, ScreenPos size) {
    return collision(position, ScreenPos(2 * CELL, 2 * CELL), p, size);
}

ScreenPos SafeSpot::get_position() {
    return position;
}