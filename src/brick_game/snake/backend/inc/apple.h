/**
 * @file apple.h
 * @brief Файл содержит класс Apple
 */
#ifndef APPLE_H
#define APPLE_H

#include <stdlib.h>

/**
 * @brief Обозначение числа яблока
 */
#define APPLE 2

/**
 * @namespace Пространство имен s21
 */
namespace s21 {
/**
 * @class Apple
 */
class Apple {
 public:
  friend class Sgame;

  /**
   * @brief Конструктор
   */
  Apple();

  /**
   * @brief Деструктор
   */
  ~Apple();

  /**
   * @brief Генерация новой позиция яблока
   */
  void newApplePosition();

 private:
  /**
   * @brief Координата x
   */
  int x_;

  /**
   * @brief Координата y
   */
  int y_;

  /**
   * @brief Значения яблока на игровом поле
   */
  int data_;
};
}  // namespace s21

#endif