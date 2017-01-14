#include "headers.h"
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <curses.h>

uint64_t frame_start;
void finish(int sig);

const int FRAMES_PER_SECOND = 60;
const float MILL_PER_FRAME = 1000.0f / FRAMES_PER_SECOND;
const uint64_t MICRO_PER_FRAME =  MILL_PER_FRAME * 1000;

void setup() {

  signal(SIGINT, finish);

  initscr();
  cbreak();
  curs_set(0);
  keypad(stdscr, 1);
  nodelay(stdscr,1);

  frame_start =  clock_gettime_nsec_np(CLOCK_MONOTONIC) / 1000;
}

Level level = Level(40, 40, level_data);
Player player = Player(20, 19);


void loop() {
  level.drawLevel();

  player.drawPlayer();

  int i;
  for ( i = 0; i < NUM_DOORS; i++ ) {
    doors[i].draw();
  }

  player.move(level, doors);
}

int main() {
    setup();
    for ( ;; ) {
      loop();

      uint64_t now =  clock_gettime_nsec_np(CLOCK_MONOTONIC) / 1000;
      uint64_t frame_length =  now - frame_start;
      uint64_t frame_left =  MICRO_PER_FRAME - frame_length;

      usleep(frame_left);
      frame_start = clock_gettime_nsec_np(CLOCK_MONOTONIC) / 1000;

    }
    finish(0);
}

void finish(int sig) {
  endwin();
  exit(sig);
}

