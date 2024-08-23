/**
 * @file map.h
 * @brief Файл содержит класс Map
 */
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>

/**
 * @brief Количество строк
 */
#define ROW 20

/**
 * @brief Количество столбцов
 */
#define COLUMNS 10

/**
 * @namespace Пространство имен s21
 */
namespace s21 {
/**
 * @class Map
 */
class Map {
 public:
  friend class Sgame;

  /**
   * @brief Конструктор
   */
  Map();

  /**
   * @brief Деструктор
   */
  ~Map();

  /**
   * @return Игровое поле
   */
  int* getMap();

  /**
   * @brief Проверяет наличие яблока на поле
   * @return false - яблоко есть || true - яблока нет
   */
  bool noApple();

  /**
   * @brief Убирает яблоко с игрового поля
   */
  void rmApple();

 private:
  /**
   * @brief Количество строк
   */
  int row_;

  /**
   * @brief Количество столбцов
   */
  int cols_;

  /**
   * @brief Vector контейнер игрового поля
   */
  std::vector<int> map_;
};
}  // namespace s21

#endif