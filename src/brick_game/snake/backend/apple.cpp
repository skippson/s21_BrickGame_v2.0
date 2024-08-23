#include "inc/apple.h"

s21::Apple::Apple() {
  x_ = 0;
  y_ = 0;
  data_ = 2;
}

void s21::Apple::newApplePosition() {
  x_ = rand() % 20;
  y_ = rand() % 10;
}

s21::Apple::~Apple() {
  x_ = 0;
  y_ = 0;
  data_ = 0;
}