#include "inc/serv.h"

s21::Sgame::Sgame() {
  std::array<int, 10> temple = {1000, 900, 800, 700, 600,
                                500,  400, 300, 200, 100};
  speed_.swap(temple);
  points_ = 0;
  highScore_ = getHighScore();
  level_ = 1;
  end_ = false;
  fail_ = false;
  win_ = false;
  eatenApple_ = true;
  snake_ = new Snake;
  map_ = new Map;
  apple_ = new Apple;
};

s21::Sgame::~Sgame() {
  delete snake_;
  delete map_;
  delete apple_;
}

s21::Sgame::Sgame(const Sgame &other) { *this = other; }

s21::Sgame &s21::Sgame::operator=(const Sgame &rhs) {
  speed_ = rhs.speed_;
  points_ = rhs.points_;
  highScore_ = rhs.highScore_;
  level_ = rhs.level_;
  end_ = rhs.end_;
  fail_ = rhs.fail_;
  win_ = rhs.win_;
  eatenApple_ = rhs.eatenApple_;
  *snake_ = *rhs.snake_;
  *map_ = *rhs.map_;
  *apple_ = *rhs.apple_;

  return *this;
}

void s21::Sgame::action(Direction move) { snake_->changeDirection(move); }

void s21::Sgame::putApple() {
  map_->map_[map_->cols_ * apple_->x_ + apple_->y_] = apple_->data_;
}

void s21::Sgame::putSnake() {
  for (size_t i = 0; i < snake_->body_.size(); i++) {
    map_->map_[map_->cols_ * snake_->body_[i].x_ + snake_->body_[i].y_] =
        snake_->body_[i].data_;
  }
}

void s21::Sgame::rmSnake() {
  for (size_t i = 0; i < snake_->body_.size(); i++) {
    map_->map_[map_->cols_ * snake_->body_[i].x_ + snake_->body_[i].y_] = 0;
  }
}

bool s21::Sgame::eatApple() {
  bool status = false;
  if (map_->noApple()) {
    snake_->newSection();
    status = true;
  }

  return status;
}

void s21::Sgame::stat() {
  points_++;
  saveScore();
  if (points_ % 5 == 0 && level_ != 10) level_++;
  if (points_ > highScore_) {
    highScore_ = points_;
  }
}

void s21::Sgame::fail() {
  if (snake_->wall() || snake_->canibalizm()) fail_ = true;
}

bool s21::Sgame::getFail() { return fail_; }

void s21::Sgame::tick() {
  rmSnake();

  if (eatenApple_) {
    apple_->newApplePosition();
    putApple();
  }
  eatenApple_ = false;
  snake_->newDirection();
  fail();
  if (!fail_) {
    putSnake();
  }
  if (eatApple()) {
    stat();
    win();
    eatenApple_ = true;
  }
}

int s21::Sgame::getSpeed() { return speed_[level_ - 1]; }

void s21::Sgame::again(bool status) {
  if (status) {
    this->~Sgame();
    points_ = 0;
    highScore_ = getHighScore();
    level_ = 1;
    end_ = false;
    win_ = false;
    fail_ = false;
    eatenApple_ = true;
    snake_ = new Snake;
    map_ = new Map;
    apple_ = new Apple;
  } else
    end_ = true;
}

int *s21::Sgame::arr() { return map_->getMap(); }

int s21::Sgame::lvl() { return level_; }

int s21::Sgame::score() { return points_; }

void s21::Sgame::saveScore() {
  if (points_ > highScore_) {
    FILE *f = fopen(".saveScoreSnake.txt", "wt");
    if (f) {
      fprintf(f, "%d", points_);
      fclose(f);
    }
  }
}

int s21::Sgame::getHighScore() {
  int x = 0;
  FILE *f = fopen(".saveScoreSnake.txt", "r");
  if (f) {
    fscanf(f, "%d", &x);
    fclose(f);
  }
  return x;
}

int s21::Sgame::highScore() { return highScore_; }

void s21::Sgame::win() {
  if (points_ == 200) win_ = true;
}

bool s21::Sgame::getWin() { return win_; }

bool s21::Sgame::getEnd() { return end_; }

void s21::Sgame::rmApple() { map_->rmApple(); }