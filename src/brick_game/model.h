/**
 * @file model.h
 * @brief Файл содержит класс Model
 */
#ifndef MODEL_H
#define MODEL_H

#include "snake/backend.h"

extern "C" {
#include "tetris/back.h"
}

/**
 * @namespace Пространство имен s21
 */
namespace s21 {
/**
 * @class Model
 */
class Model {
 public:
  /**
   * @brief Конструктор
   */
  Model();

  /**
   * @brief Деструктор
   */
  ~Model();

  /**
   * @brief Конструктор копирования
   */
  Model(const Model &other);

  /**
   * @brief Оператор присваивания
   */
  Model &operator=(const Model &rhs);

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
   * @brief Модель змейки
   */
  Sgame *snake_;

  /**
   * @brief Модель тетриса
   */
  Tgame *tetris_;
};
}  // namespace s21

#endif
