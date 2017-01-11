
#include <stdlib.h>
#include <curses.h>
#include <signal.h>

int player_x = 20;
int player_y = 20;
int player_x_old = player_x;
int player_y_old = player_y;

void drawPlayer() {
  int i;
  int j;
  for ( i = 0; i <= 1; i++ ) {
    for ( j = 0; j <= 1; j++ ) {
      mvaddch(player_y_old + j, player_x_old + i, ' ');
      mvaddch(player_y + j, player_x + i, 'P');
    }
  }
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

