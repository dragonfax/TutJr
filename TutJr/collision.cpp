#include "headers.h"

// simple AABB

// does shapes collide at all?
bool collision(ScreenPos pa, ScreenPos sizea, ScreenPos pb, ScreenPos sizeb) {

  ScreenPos la = pa + sizea - ScreenPos(1,1);
  ScreenPos lb = pb + sizeb - ScreenPos(1,1);

  return ! ( pa.x > lb.x || pa.y > lb.y || pb.x > la.x || pb.y > la.y );
}

// does shape a completely lie within shape b.
bool enclosure(ScreenPos pa, ScreenPos sizea, ScreenPos pb, ScreenPos sizeb) {

  // while pa is the upper left of the shape, 
  // we need the lower right (la).
  
  ScreenPos la = pa + sizea - ScreenPos(1,1);
  ScreenPos lb = pb + sizeb - ScreenPos(1,1);

  return pa.x >= pb.x && pa.y >= pb.y && la.x <= lb.x && la.y <= lb.y;
}

