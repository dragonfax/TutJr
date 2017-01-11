
#include <stdlib.h>
#include <curses.h>
#include <signal.h>

int player_x = 20;
int player_y = 20;
int player_x_old = player_x;
int player_y_old = player_y;

void drawPlayer() {
  mvaddch(player_y_old, player_x_old, ' ');
  mvaddch(player_y, player_x, 'P');
  refresh();
}

static void finish(int sig);

void setup() {

  signal(SIGINT, finish);

  initscr();
  cbreak();
  curs_set(0);
  keypad(stdscr, 1);
  nodelay(stdscr,1);
}

void loop() {
  drawPlayer();

  int c = getch();
  player_x_old = player_x;
  player_y_old = player_y;
  if ( c == KEY_LEFT ) {
    player_x -= 1;
  } else if ( c == KEY_RIGHT ) {
    player_x += 1;
  } else if ( c == KEY_UP ) {
    player_y -= 1;
  } else if ( c == KEY_DOWN ) {
    player_y += 1;
  }
}

int main() {
    setup();
    for ( ;; ) {
      loop();
    }
    finish(0);
}

static void finish(int sig) {
  endwin();
  exit(sig);
}

