#include "headers.h"

// simple AABB
bool collision(Pos p1, int w1, int h1, Pos p2, int w2, int h2) {

  int i1;
  int j1;
  for ( i1 = 0; i1 < s1; i1++ ) {
    for ( j1 = 0; j1 < s1; j1++ ) {
      int i2;
      int j2;
      for ( i2 = 0; i2 < s2; i2++ ) {
        for ( j2 = 0; j2 < s2; j2++ ) {
          Pos np1 = p1 + Pos(i1, j1);
          Pos np2 = p2 + Pos(i2, j2);
          if ( np1 == np2 ) {
            return true;
          }
        }
      }
    }
  }

  return false;
}


