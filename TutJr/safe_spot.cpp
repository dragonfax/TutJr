#include "headers.h"

SafeSpot::SafeSpot() {}

SafeSpot::SafeSpot(MapPos cell) {
    position = cell_to_screen(cell);
}

bool SafeSpot::collides_with(ScreenPos p, ScreenPos size) {
    return collision(position, ScreenPos(SPACE_SIZE, SPACE_SIZE), p, size);
}

ScreenPos SafeSpot::get_position() {
    return position;
}