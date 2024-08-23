/*!
 * \mainpage
 * \author semberlo
 * \version 1.0
 *
 * \section intro_sec Snake && Tetris
 * Проект создан при помощи:
 * 1. C language
 * 2. C++ language
 * 3. ncurses
 * 4. Qt creator
 * 5. Pattern MVC
 * 6. Doxygen
 * 7. CMake
 *
 * \section brief_sec Brief
 * BrickGame — популярная портативная консоль 90-ых годов с несколькими тысячами
 * встроенными играми, разработанная в Китае. Изначально была копией
 * разработанной в СССР и выпущенной Nintendo в рамках платформы GameBoy игры
 * «Тетрис», но включала в себя также и множество других игр, которые
 * добавлялись с течением времени. Консоль имела небольшой экранчик с игровым
 * полем размера 10х20, представляющим из себя матрицу «пикселей». Справа от
 * поля находилось табло с цифровой индикацией состояния текущей игры, рекордами
 * и прочей дополнительной информацией. Самыми распространенными играми на
 * BrickGame были: тетрис, танки, гонки, фроггер и змейка.
 *
 * В данном проекте реализована игра из серии BrickGame -
 * Snake. Так же имеет самую популярную игру серии BrickGame - Tetris, реализованную в прошлом проекте.
 *
 */
#include "brick_game/model.h"
#include "controller/controller.h"
#include "gui/desktop/desk.h"

int main(int argc, char **argv) {
  s21::Model model;
  s21::Controller controller(&model);
  QApplication app(argc, argv);
  s21::View view(&controller);

  return app.exec();
}