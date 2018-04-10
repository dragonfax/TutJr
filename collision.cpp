#include "headers.h"

// simple AABB

// does shapes collide at all?
bool collision(Pos pa, byte wa, byte ha, Pos pb, byte wb, byte hb) {

  Pos la = pa + Pos(wa - 1, ha - 1);
  Pos lb = pb + Pos(wb - 1, hb - 1);

  return ! ( pa.x > lb.x || pa.y > lb.y || pb.x > la.x || pb.y > la.y );
}

// does shape a completely lie within shape b.
bool enclosure(Pos pa, byte wa, byte ha, Pos pb, byte wb, byte hb) {

  // while pa is the upper left of the shape, 
  // we need the lower right (la).
  
  Pos la = pa + Pos(wa - 1, ha - 1);
  Pos lb = pb + Pos(wb - 1, hb - 1);

  return pa.x >= pb.x && pa.y >= pb.y && la.x <= lb.x && la.y <= lb.y;
}

Pos cell_to_screen(Pos cell) {
  return Pos(cell.x * CELL + cell.x * WALL, cell.y * CELL + cell.y * WALL);
}

Pos screen_to_cell(Pos position) {
  return Pos(position.x / ( CELL + WALL ), position.y / ( CELL + WALL ) );
}
