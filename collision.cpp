#include "headers.h"

// simple AABB

// does shapes collide at all?
bool collision(Pos pa, int wa, int ha, Pos pb, int wb, int hb) {

  Pos la = pa + Pos(wa - 1, ha - 1);
  Pos lb = pb + Pos(wb - 1, hb - 1);

  return ! ( pa.x > lb.x || pa.y > lb.y || pb.x > la.x || pb.y > la.y );
}

// does shape a completely lie within shape b.
bool enclosure(Pos pa, int wa, int ha, Pos pb, int wb, int hb) {

  // while pa is the upper left of the shape, 
  // we need the lower right (la).
  
  Pos la = pa + Pos(wa - 1, ha - 1);
  Pos lb = pb + Pos(wb - 1, hb - 1);

  return pa.x >= pb.x && pa.y >= pb.y && la.x <= lb.x && la.y <= lb.y;
}

