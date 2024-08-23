#include "../backend.h"

s21::Map::Map() {
  row_ = ROW;
  cols_ = COLUMNS;
  for (int i = 0; i < 20 * 10; i++) {
    map_.push_back(0);
  }
}

s21::Map::~Map() {
  row_ = 0;
  cols_ = 0;
}

int *s21::Map::getMap() { return map_.data(); }

bool s21::Map::noApple() {
  bool status = true;
  for (size_t i = 0; i < map_.size(); i++) {
    if (map_[i] == APPLE) {
      status = false;
    }
  }

  return status;
}

void s21::Map::rmApple() {
  for (size_t i = 0; i < map_.size(); i++) {
    if (map_[i] == APPLE) map_[i] = 0;
  }
}