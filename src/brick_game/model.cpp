#include "model.h"

s21::Model::Model() {
  snake_ = new Sgame;
  tetris_ = new Tgame;
  *tetris_ = gameInit();
}

s21::Model::~Model() {
  delete snake_;
  delete tetris_;
}

s21::Model::Model(const Model &other) {
  snake_ = new Sgame;
  tetris_ = new Tgame;
}

s21::Model &s21::Model::operator=(const Model &rhs) {
  snake_ = rhs.snake_;
  tetris_ = rhs.tetris_;

  return *this;
}

void s21::Model::tick() { return snake_->tick(); }

int *s21::Model::map() { return snake_->arr(); }

int s21::Model::lvl() { return snake_->lvl(); }

int s21::Model::score() { return snake_->score(); }

int s21::Model::highScore() { return snake_->highScore(); }

void s21::Model::left() { snake_->action(LEFT); }

void s21::Model::right() { snake_->action(RIGHT); }

void s21::Model::up() { snake_->action(UP); }

void s21::Model::down() { snake_->action(DOWN); }

void s21::Model::non() { snake_->action(NON); }

void s21::Model::again(bool status) { snake_->again(status); }

bool s21::Model::fail() { return snake_->getFail(); }

bool s21::Model::end() { return snake_->getEnd(); }

bool s21::Model::win() { return snake_->getWin(); }

int s21::Model::speed() { return snake_->getSpeed(); }

void s21::Model::left_t() { moveX(tetris_, -1); }

void s21::Model::right_t() { moveX(tetris_, 1); }

void s21::Model::up_t() { moveRotate(tetris_, 1); }

void s21::Model::down_t() { moveDown(tetris_); }

void s21::Model::drop_t() { moveDrop(tetris_); }

void s21::Model::again_t(bool status) { againGame(tetris_, status); }

void s21::Model::tick_t() { ticker(tetris_); }

int *s21::Model::map_t() { return tetris_->field; }

int s21::Model::lvl_t() { return tetris_->level; }

int s21::Model::score_t() { return tetris_->score; }

int s21::Model::highScore_t() { return tetris_->highScore; }

int s21::Model::nextTetrType() { return tetris_->next->type; }

int s21::Model::nextTetrOrint() { return tetris_->next->orintation; }

bool s21::Model::fail_t() { return gameOver(tetris_); }