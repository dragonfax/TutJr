#include "headers.h"
#include <unistd.h>
#include <stdlib.h>

Arduboy arduboy;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.display();
}

void draw() {
  arduboy.clear();
      
  level.draw();

  player.draw();

  byte i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    doors[i].draw();
  }

  for ( i = 0; i < NUM_MONSTERS; i++ ) {
    monsters[i].draw();
  }

  arduboy.display();
}

void move() {

  player.move();

  int i;
  for ( i = 0; i < NUM_MONSTERS; i++ ) {
    monsters[i].move();
  }
}

void loop() {

  if ( ! arduboy.nextFrame() ) {
    return;
  }

  draw();

  move();
}

