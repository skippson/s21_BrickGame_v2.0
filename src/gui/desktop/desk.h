/**
 * @file desk.h
 * @brief Файл содержит функции отрисовки игры в приложении в классе View
 */
#ifndef DESK_H
#define DESK_H

#include <time.h>
#include <unistd.h>

#include <QApplication>
#include <QDebug>
#include <QGroupBox>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QRectF>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <chrono>
#include <iostream>
#include <thread>

#include "../../controller/controller.h"
#include "mainwindow.h"

/**
 * @namespace Пространство имен s21
 */
namespace s21 {
/**
 * @class View, наследует QWidget
 */
class View : public QWidget {
 private:
  /**
   * @brief Контроллер игры
   */
  Controller *controller_;

  /**
   * @brief Таймер айди
   */
  int timerId_;

  /**
   * @brief Флаг игры в тетрис
   */
  bool tetris_;

  /**
   * @brief Флаг игры в змейку
   */
  bool snake_;

  /**
   * @brief Флаг начала новой игры
   */
  bool again_;

  /**
   * @brief Флаг, что игра идет
   */
  bool go_;

  /**
   * @brief Флаг паузы
   */
  bool pause_;

  /**
   * @brief Флаг победы для змейки
   */
  bool win_;

  /**
   * @brief Флаг старта игры
   */
  bool start_;

 protected:
  /**
   * @brief Метод, вызываемый по таймеру, в данном случае показ окон(отрисовка)
   * и игровой цикл
   * @param QTimerEvent
   */
  void timerEvent(QTimerEvent *) override;

  /**
   * @brief Метод, вызываемый при нажатии клавиши
   * @param QKeyEvent
   */
  void keyPressEvent(QKeyEvent *) override;

  /**
   * @brief Орисовка игры, по таймеру
   * @param QPaintEvent
   */
  void paintEvent(QPaintEvent *) override;

 public:
  /**
   * @brief Конструктор вьюера
   */
  View(Controller *controller);

  /**
   * @brief Деструктор
   */
  ~View() { deleteGame(); }

  /**
   * @brief Очистка памяти
   */
  void deleteGame();

  /**
   * @brief Действие игрока змейки
   * @param action Действие игрока
   */
  void action(int action);

  /**
   * @brief Отрисовка следующего тетрамино(при тетрисе)
   * @param QPainter
   */
  void drawNext(QPainter *qp);

  /**
   * @brief Игровой цикл змейки
   * @param QPainter
   */
  void snake(QPainter *qp);

  /**
   * @brief Игровой цикл тетриса
   * @param QPainter
   */
  void tetris(QPainter *qp);

  /**
   * @brief Действие игрока тетриса
   * @param action Действие игрока
   */
  void action_t(int action);

  /**
   * @brief Действие игрока при перезапуске
   * @param key Ключ, выбор игрока(для считывания)
   */
  void actionAgain(int key);

  /**
   * @brief Действие игрока при меню
   * @param key Ключ, выбор игрока(для считывания)
   */
  void actionMenu(int key);

  /**
   * @brief Отрисовка параметров игрока
   * @param QPainter
   */
  void drawRecs(QPainter *);

  /**
   * @brief Отрисовка игрового поля
   * @param QPainter
   */
  void drawField(QPainter *);

  /**
   * @brief Показ меню
   */
  void menu();

  /**
   * @brief Показ меню перезапуска
   */
  void again();

  /**
   * @brief Показ паузы
   */
  void pause();

  /**
   * @brief Показ победы при змейки
   */
  void win();

  /**
   * @brief Установка параметров
   */
  void set_labels();

  /**
   * @brief Таймер
   */
  void timer();

  /**
   * @brief QVBoxLayout
   */
  QVBoxLayout *mainLayout;

  /**
   * @brief QGroupBox
   */
  QGroupBox *stats_box;

  /**
   * @brief QGroupBox
   */
  QGroupBox *again_box;

  /**
   * @brief QLabel
   */
  QLabel *labels[10];
};
}  // namespace s21

#endif  // GAME_H