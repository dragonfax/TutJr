
#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <stdbool.h>

char *level[] = { 
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "W                                      W",
  "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW@W"
};

int player_x = 20;
int player_y = 20;
int player_x_old = player_x;
int player_y_old = player_y;

void drawLevel() {
  int i;
  int j;
  for ( i = 0; i < 40; i++ ) {
    for ( j = 0; j < 40; j++ ) {
      mvaddch(j,i, level[j][i]);
    }
  }
}

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
  drawLevel();
  drawPlayer();

  int c = getch();

  int player_x_new = player_x;
  int player_y_new = player_y;
  if ( c == KEY_LEFT ) {
    player_x_new -= 1;
  } else if ( c == KEY_RIGHT ) {
    player_x_new += 1;
  } else if ( c == KEY_UP ) {
    player_y_new -= 1;
  } else if ( c == KEY_DOWN ) {
    player_y_new += 1;
  }

  // check for collision
  int i, j;
  bool collision = false;
  for ( i = 0; i <= 1; i++ ) {
    for ( j = 0; j <= 1; j++ ) {
      if ( level[player_y_new + i][player_x_new + j] != ' ' ) {
        collision = true;
      }
    }
  }

  if ( ! collision ) {
    player_x_old = player_x;
    player_y_old = player_y;
    player_x = player_x_new;
    player_y = player_y_new;
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

