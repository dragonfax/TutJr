#include "headers.h"
#include <unistd.h>
#include <stdlib.h>

Arduboy arduboy;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.display();

}

Level level = Level(LEVEL_WIDTH, LEVEL_HEIGHT, level_data);
Player player = Player(10, 5);


void loop() {

  if (!(arduboy.nextFrame()))
    return;
    
  arduboy.clear();
      
  level.drawLevel();

  player.drawPlayer();

  int i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    doors[i].draw();
  }

  for ( i = 0; i < NUM_MONSTERS; i++ ) {
    monsters[i].draw();
  }

  refresh();

  player.move(level, doors);

  for ( i = 0; i < NUM_MONSTERS; i++ ) {
    monsters[i].move();
  }
}

