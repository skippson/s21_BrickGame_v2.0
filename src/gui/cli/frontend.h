/**
 * @file frontend.h
 * @brief Файл содержит функции консольной отрисовки игры в классе View
 */
#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../controller/controller.h"

/**
 * @brief Для ncurses
 */
#define _POSIX_C_SOURCE 199309L

/**
 * @brief Один блок на два столбца
 */
#define COLSPERCELL 2

/**
 * @brief Макрос на отрисовку заполненного блока
 */
#define ADDBLOCK(w, x)                          \
  waddch((w), ' ' | A_REVERSE | COLOR_PAIR(x)); \
  waddch((w), ' ' | A_REVERSE | COLOR_PAIR(x))

/**
 * @brief Макрос на отрисовку пусnого блока
 */
#define ADDEMPTY(w) \
  waddch((w), ' '); \
  waddch((w), ' ')

/**
 * @brief Макрос на нициализацию ncurses
 */
#define CURSINIT()        \
  {                       \
    initscr();            \
    cbreak();             \
    noecho();             \
    keypad(stdscr, TRUE); \
    timeout(0);           \
    curs_set(0);          \
    initColors();         \
  }

/**
 * @brief Макрос на нициализацию 2 окон
 * Выставление размеров и начала координат в окне
 */
#define WINDOWINIT2(x, z)                              \
  {                                                    \
    int row = 0, col = 0;                              \
    getmaxyx(stdscr, row, col);                        \
    x = newwin(20 + 2, 2 * 10 + 2, row / 10, col / 3); \
    z = newwin(5, 20, 14, col / 1.4);                  \
  }

/**
 * @brief Макрос на нициализацию 3 окон
 * Выставление размеров и начала координат в окне
 */
#define WINDOWINIT3(x, y, z)                           \
  {                                                    \
    int row = 0, col = 0;                              \
    getmaxyx(stdscr, row, col);                        \
    x = newwin(20 + 2, 2 * 10 + 2, row / 10, col / 3); \
    y = newwin(4, 11, row / 7, col / 1.4);             \
    z = newwin(5, 20, 14, col / 1.4);                  \
  }

/**
 * @namespace Пространство имен s21
 */
namespace s21 {
/**
 * @class View
 */
class View {
 public:
  /**
   * @brief Конструктор вьюера
   */
  explicit View(Controller *c) : controller_(c){};

  /**
   * @brief Game loop
   */
  void show();

 private:
  /**
   * @brief Отрисовка старта игры
   */
  void start();

  /**
   * @brief Отрисовка паузы игры
   */
  void pause();

  /**
   * @brief Отрисовка запроса о перезапуске игры и начало новой или завершения
   * игры змейки
   * @param score Очки игрока
   * @return true - начало новой игры | false - конец игры
   */
  bool again(int score);

  /**
   * @brief Отрисовка победы игрока и начало новой или завершения змейки
   * @return true - начало новой игры | false - конец игры
   */
  bool win();

  /**
   * @brief Действие игрока змейки
   */
  void action();

  /**
   * @brief Игровой цикл змейки
   */
  void snake();

  /**
   * @brief Игровой цикл тетриса
   */
  void tetris();

  /**
   * @brief Таймер для тетриса
   */
  void timer();

  /**
   * @brief Действие игрока тетриса
   * @param status Статус игрового цикла
   */
  void action_t(bool *status);

  /**
   * @brief Орисовка меню
   */
  int menu();

  /**
   * @brief Функция отрисовки игровой статистики
   * @param w Окно отрисовки
   * @param level Уровень игрока
   * @param score Очки игрока
   * @param highScore Рекорд
   */
  void printStat(WINDOW *w, int level, int score, int hidhScore);

  /**
   * @brief Функция отрисовки игровой статистики
   * @param w Окно отрисовки
   * @param board Игровое поле
   */
  void printField(WINDOW *w, int *board);

  /**
   * @brief Функция отрисовки игровой статистики
   * @param w Окно отрисовки
   * @param type Тип тетрамино
   * @param orint Ориентация тетрамино
   */
  void printNext(WINDOW *w, int type, int orint);

  /**
   * @brief Контроллер игры
   */
  Controller *controller_;
};
}  // namespace s21

#endif