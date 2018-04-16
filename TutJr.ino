#include "headers.h"
#include <unistd.h>
#include <stdlib.h>

Arduboy arduboy;

Player player = Player();

void setup() {
  arduboy.beginNoLogo();
  arduboy.setFrameRate(60);
  begin();
  arduboy.display();
  // Serial.begin(9600);
}

void begin() {
  respawn();
}

void respawn() {
  player.lives -= 1;
  if player.lives < 0 ) {
    end("You Lose");
  }
  player.position = level.entrance.position;
}


void draw() {
  arduboy.clear();
      
  level.draw();

  exitSpace.draw();

  player.draw();

  byte i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    level_doors[i].draw();
  }

  for ( i = 0; i < NUM_MONSTERS; i++ ) {
    monsters[i].draw();
  }

  lives_draw();

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

void win() {
  arduboy.clear();
  drawString(10, 10, "You Win");
  arduboy.display();
  delay( 3 * 1000);
  exit(0);
}
      
void drawString(byte x, byte y, const char* str){
  byte offset = 0;
  byte i;
  for ( i = 0; i < strlen(str); i++ ) {
    arduboy.drawChar(x + offset, y, str[i], WHITE, BLACK, 1);
    offset += 8;
  }
}

