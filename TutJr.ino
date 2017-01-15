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

  exitSpace.draw();

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


void end(const char *str) {
  arduboy.clear();
  drawString(10, 10, str);
  arduboy.display();
  delay( 3 * 1000);
  exit(0);
}
      
void drawString(byte x, byte y, const char* str){
  byte offset;
  byte i;
  for ( i = 0; i < strlen(str); i++ ) {
    arduboy.drawChar(x + offset, y, str[i], WHITE, BLACK, 1);
    offset += 8;
  }
}

