/**
 * @file body.h
 * @brief Файл содержит класс Body
 */
#ifndef BODY_H
#define BODY_H

#include <vector>

/**
 * @namespace Пространство имен s21
 */
namespace s21 {
/**
 * @class Body
 */
class Body {
 public:
  friend class Snake;
  friend class Sgame;

  /**
   * @brief Конструктор по умолчанию
   */
  Body();

  /**
   * @brief Конструктор, присваивающий заданные координаты
   * @param x Координата х
   * @param y Координата y
   */
  Body(int x, int y);

  /**
   * @brief Деструктор
   */
  ~Body();

  /**
   * @brief Движение по оси x
   * @param os обозначение влево/вправо, где:
   * -1 влево,
   * 1 вправо
   */
  void moveX(const int os);

  /**
   * @brief Движение по оси y
   * @param os обозначение влево/вправо, где:
   * -1 вверх,
   * 1 вниз
   */
  void moveY(const int os);

 private:
  /**
   * @brief Координата х
   */
  int x_;

  /**
   * @brief Координата y
   */
  int y_;

  /**
   * @brief Значение части тела змеи на игровом поле
   */
  int data_;
};

/**
 * @brief Обозначния движения
 */
typedef enum {
  NON,
  DOWN,
  UP,
  LEFT,
  RIGHT,
} Direction;

}  // namespace s21

#endif