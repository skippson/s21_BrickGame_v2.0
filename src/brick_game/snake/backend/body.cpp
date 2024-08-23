#include "inc/body.h"

s21::Body::Body() {
  x_ = 5;
  y_ = 5;
  data_ = 1;
}

s21::Body::Body(int x, int y) {
  x_ = x;
  y_ = y;
  data_ = 1;
}

s21::Body::~Body() {
  x_ = 0;
  y_ = 0;
  data_ = 0;
}

void s21::Body::moveX(const int os) { y_ += os; }

void s21::Body::moveY(const int os) { x_ += os; }