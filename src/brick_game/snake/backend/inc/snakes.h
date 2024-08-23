/**
 * @file snakes.h
 * @brief Файл содержит класс Snake
 */
#ifndef SNAKES_H
#define SNAKES_H

#include <stdbool.h>

#include "body.h"
#include "map.h"

/**
 * @namespace Пространство имен s21
 */
namespace s21 {
/**
 * @class Snake
 */
class Snake {
 public:
  friend class Sgame;

  /**
   * @brief Конструктор
   */
  Snake();

  /**
   * @brief Деструктор
   */
  ~Snake();

  /**
   * @brief Проверяет движение змеи
   * @param direction Направление движения
   * @return false - движение невозможно || true - движение возможно
   */
  bool checkDirection(const Direction &direction);

  /**
   * @brief Смена текущего напрявление на следующее, если оно возможно
   * @param direction Направление движения
   */
  void changeDirection(const Direction &direction);

  /**
   * @brief Совершение движения(смена координат)
   */
  void newDirection();

  /**
   * @brief Создание нового сегмента змеи
   */
  void newSection();

  /**
   * @brief Проверка на столкновение головы змеи со стеной
   * @return true - мама вызывай гибдд || false -  не столкнулась
   */
  bool wall();

  /**
   * @brief Проверка на столкновение головы змеи со своей тушей
   * @return true - поедание себя || false -  не столкнулась
   */
  bool canibalizm();

 private:
  /**
   * @brief Текущее направление
   */
  Direction direction_;

  /**
   * @brief Следующее направление
   */
  Direction nextDirection_;

  /**
   * @brief Vector контейнер обозначающий змею, содержит в себе класс Body
   */
  std::vector<Body> body_;
};
}  // namespace s21

#endif