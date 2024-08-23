/**
 * @file controller.h
 * @brief Файл содержит класс Controller
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>

#include "../brick_game/model.h"

/**
 * @namespace Пространство имен s21
 */
namespace s21 {
/**
 * @class Model
 */
class Controller {
 public:
  /**
   * @brief Конструктор контроллера
   */
  explicit Controller(Model *model) : model_(model){};

  /**
   * @brief Игровой такт змейки (тик)
   */
  void tick();

  /**
   * @return Игровое поле змейки
   */
  int *map();

  /**
   * @return Уровень игрока змейки
   */
  int lvl();

  /**
   * @return Возвращает количество очков змейки
   */
  int score();

  /**
   * @return Рекордное значение в змейку
   */
  int highScore();

  /**
   * @brief Движение змейки влево
   */
  void left();

  /**
   * @brief Движение змейки вправо
   */
  void right();

  /**
   * @brief Движение змейки вверх
   */
  void up();

  /**
   * @brief Движение змейки вниз
   */
  void down();

  /**
   * @brief Новая игра в змейку
   * @param status true - новая игра | false - игра окончена
   */
  void again(bool status);

  /**
   * @brief Бездвействие игрока
   */
  void non();

  /**
   * @return Флаг окончания игры в змейку
   */
  bool end();

  /**
   * @return Флаг победы игрока в змейку
   */
  bool win();

  /**
   * @return Флаг ошибки игрока
   */
  bool fail();

  /**
   * @return Значение скорости
   */
  int speed();

  /**
   * @return Координаты столбцов блока
   */
  int nextTetrCol(int tetr, int ori, int cel);

  /**
   * @return Координаты строк блока
   */
  int nextTetrRow(int tetr, int ori, int row);

  /**
   * @brief Движение тетрамино влево
   */
  void left_t();

  /**
   * @brief Движение тетрамино вправо
   */
  void right_t();

  /**
   * @brief Поворот тетрамино
   */
  void up_t();

  /**
   * @brief Движение тетрамино вниз
   */
  void down_t();

  /**
   * @brief Движение тетрамино до конца вниз
   */
  void drop_t();

  /**
   * @brief Новая игра в тетрис
   * @param status true - новая игра | false - игра окончена
   */
  void again_t(bool status);

  /**
   * @brief Игровой такт тетриса (тик)
   */
  void tick_t();

  /**
   * @return Игровое поле тетриса
   */
  int *map_t();

  /**
   * @return Уровень игрока в тетрис
   */
  int lvl_t();

  /**
   * @return Количество очков в тетрис
   */
  int score_t();

  /**
   * @return Рекорд игрока в тетрис
   */
  int highScore_t();

  /**
   * @return Тип следующего тетрамино
   */
  int nextTetrType();

  /**
   * @return Ориентация следующего тетрамино
   */
  int nextTetrOrint();

  /**
   * @return Ошибка игрока в тетрис
   */
  bool fail_t();

 private:
  /**
   * @brief Игровая модель
   */
  Model *model_;
};
}  // namespace s21
#endif