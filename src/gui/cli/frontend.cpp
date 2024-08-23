#include "frontend.h"

void s21::View::printField(WINDOW *w, int *board) {
  box(w, 0, 0);
  for (int i = 0; i < 20; i++) {
    wmove(w, 1 + i, 1);
    for (int j = 0; j < 10; j++) {
      if (board[10 * i + j] != 0) {
        waddch((w), ' ' | A_REVERSE | COLOR_PAIR(board[10 * i + j]));
        waddch((w), ' ' | A_REVERSE | COLOR_PAIR(board[10 * i + j]));
      } else {
        waddch((w), ' ');
        waddch((w), ' ');
      }
    }
  }
  wnoutrefresh(w);
}

void s21::View::printNext(WINDOW *w, int type, int orint) {
  wclear(w);
  box(w, 0, 0);
  if (type == -1) {
    wnoutrefresh(w);
    return;
  }
  for (int i = 0; i < CELLS; i++) {
    wmove(w, controller_->nextTetrRow(type, orint, i) + 1,
          controller_->nextTetrCol(type, orint, i) * 2 + 2);
    ADDBLOCK(w, TYPETOCELL(type));
  }
  wnoutrefresh(w);
}

void s21::View::printStat(WINDOW *w, int level, int score, int highScore) {
  wclear(w);
  box(w, 0, 0);
  wmove(w, 1, 5);
  wprintw(w, "Level: %d\n", level);
  wprintw(w, "     Score: %d\n", score);
  wprintw(w, "   High score: %d\n", highScore);

  wnoutrefresh(w);
}

void initColors() {
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);
  init_pair(6, COLOR_BLUE, COLOR_BLACK);
  init_pair(7, COLOR_CYAN, COLOR_BLACK);
}

void s21::View::start() {
  int row = 0, col = 0;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 2);
  printw("START");
  refresh();
  bool status = true;
  while (status) {
    switch (getch()) {
      case ' ':
        status = false;
        break;
      default:
        break;
    }
  }
  clear();
}

void s21::View::pause() {
  clear();
  int row = 0, col = 0;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 2);
  printw("PAUSE");
  refresh();
  bool status = true;
  while (status) {
    switch (getch()) {
      case ' ':
        status = false;
        break;
      default:
        break;
    }
  }
  clear();
}

bool s21::View::again(int score) {
  clear();
  int row = 0, col = 0;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 4);
  printw("The game is over, you have %d points. Want to start over?[y/n]",
         score);
  refresh();
  bool status = false;
  bool w = true;
  while (w) {
    switch (getch()) {
      case 'y':
        status = true;
        w = false;
        break;
      case 'n':
        status = false;
        w = false;
        break;
      default:
        break;
    }
  }
  clear();

  return status;
}

bool s21::View::win() {
  clear();
  int row = 0, col = 0;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 4);
  printw("You won! You managed to collect 200 points. Want to try again?[y/n]");
  refresh();
  bool status = false;
  bool w = true;
  while (w) {
    switch (getch()) {
      case 'y':
        status = true;
        w = false;
        break;
      case 'n':
        status = false;
        w = false;
        break;
      default:
        break;
    }
  }
  clear();

  return status;
}

void s21::View::snake() {
  controller_->again(true);
  start();

  WINDOW *board = NULL, *score = NULL;
  WINDOWINIT2(board, score);

  while (controller_->end()) {
    action();
    controller_->tick();

    if (controller_->win()) {
      controller_->again(win());
    }

    if (controller_->fail()) {
      controller_->again(again(controller_->score()));
    }

    printField(board, controller_->map());
    printStat(score, controller_->lvl(), controller_->score(),
              controller_->highScore());

    doupdate();
    timeout(controller_->speed());
  }
}

void s21::View::tetris() {
  controller_->again_t(true);

  start();

  WINDOW *board = NULL, *next = NULL, *score = NULL;
  WINDOWINIT3(board, next, score);

  bool status = true;

  while (status) {
    controller_->tick_t();

    action_t(&status);

    if (status) {
      printField(board, controller_->map_t());
      printNext(next, controller_->nextTetrType(),
                controller_->nextTetrOrint());
      printStat(score, controller_->lvl_t(), controller_->score_t(),
                controller_->highScore_t());
    }

    doupdate();
    timer();

    if (controller_->fail_t()) {
      status = again(controller_->score_t());
      if (status) {
        controller_->again_t(true);
      }
    }
  }
}

int s21::View::menu() {
  CURSINIT();
  clear();
  int row = 0, col = 0;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 3);
  printw("BRICK GAME: SNAKE[1] TETRIS[2] QUIT[q]");
  refresh();
  int choice = 0;
  bool status = true;
  while (status) {
    switch (getch()) {
      case '1':
        choice = 1;
        status = false;
        break;
      case '2':
        choice = 2;
        status = false;
        break;
      case 'q':
        choice = 3;
        status = false;
      default:
        break;
    }
  }

  clear();

  return choice;
}
void s21::View::show() {
  bool status = true;
  while (status) {
    int choice = menu();
    if (choice == 1) snake();
    if (choice == 2) tetris();
    if (choice == 3) status = false;
  }

  wclear(stdscr);
  endwin();
}

void s21::View::action() {
  switch (getch()) {
    case KEY_LEFT:
      controller_->left();
      break;
    case KEY_RIGHT:
      controller_->right();
      break;
    case KEY_UP:
      controller_->up();
      break;
    case KEY_DOWN:
      controller_->down();
      break;
    case 'q':
      controller_->again(again(controller_->score()));
      break;
    case 'p':
      pause();
      break;
    default:
      controller_->non();
      break;
  }
}

void s21::View::action_t(bool *status) {
  bool temple = false;
  switch (getch()) {
    case KEY_LEFT:
      controller_->left_t();
      break;
    case KEY_RIGHT:
      controller_->right_t();
      break;
    case KEY_UP:
      controller_->up_t();
      break;
    case KEY_DOWN:
      controller_->down_t();
      break;
    case 'q':
      temple = again(controller_->score());
      if (temple) {
        controller_->again_t(true);
      } else {
        *status = false;
      }
      break;
    case 'p':
      pause();
      break;
    case ' ':
      controller_->drop_t();
      break;
    default:
      break;
  }
}

void s21::View::timer() {
  struct timespec timer = {0};
  timer.tv_sec = 0;
  timer.tv_nsec = 10000 * 1000;
  nanosleep(&timer, NULL);
}