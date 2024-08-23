#include "inc/snakes.h"

s21::Snake::Snake() {
  direction_ = DOWN;
  nextDirection_ = DOWN;
  body_.push_back(Body());
  body_[0].data_ = 3;
  body_.push_back(Body(5, 6));
  body_.push_back(Body(5, 7));
}

s21::Snake::~Snake() {
  direction_ = NON;
  nextDirection_ = NON;
}

bool s21::Snake::checkDirection(const Direction &direction) {
  bool status = true;

  if ((direction_ == RIGHT && direction == LEFT) ||
      (direction_ == LEFT && direction == RIGHT)) {
    status = false;
  }

  if ((direction_ == UP && direction == DOWN) ||
      (direction_ == DOWN && direction == UP)) {
    status = false;
  }

  if (direction == NON) {
    status = false;
  }

  return status;
}

void s21::Snake::changeDirection(const Direction &direction) {
  if (checkDirection(direction)) {
    nextDirection_ = direction;
  } else
    nextDirection_ = direction_;
}

void s21::Snake::newDirection() {
  for (size_t i = body_.size() - 1; i > 0; i--) {
    body_[i].x_ = body_[i - 1].x_;
    body_[i].y_ = body_[i - 1].y_;
  }
  if (nextDirection_ == LEFT) body_[0].moveX(-1);
  if (nextDirection_ == RIGHT) body_[0].moveX(1);
  if (nextDirection_ == UP) body_[0].moveY(-1);
  if (nextDirection_ == DOWN) body_[0].moveY(1);

  direction_ = nextDirection_;
}

void s21::Snake::newSection() {
  int last = body_.size();
  if (direction_ == LEFT) {
    body_.push_back(Body(body_[last - 1].x_, body_[last - 1].y_ + 1));
  }

  if (direction_ == RIGHT) {
    body_.push_back(Body(body_[last - 1].x_, body_[last - 1].y_ - 1));
  }

  if (direction_ == UP) {
    body_.push_back(Body(body_[last - 1].x_ + 1, body_[last - 1].y_));
  }

  if (direction_ == DOWN) {
    body_.push_back(Body(body_[last - 1].x_ - 1, body_[last - 1].y_));
  }
}

bool s21::Snake::wall() {
  bool status = false;
  if (body_[0].x_ >= 20 || body_[0].x_ < 0) {
    status = true;
  }

  if (body_[0].y_ > 10 || body_[0].y_ < 0) {
    status = true;
  }

  return status;
}

bool s21::Snake::canibalizm() {
  bool status = false;
  for (size_t i = 1; i < body_.size(); i++) {
    if (body_[0].x_ == body_[i].x_ && body_[0].y_ == body_[i].y_) {
      status = true;
      break;
    }
  }

  return status;
}