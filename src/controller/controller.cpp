#include "controller.h"

void s21::Controller::tick() { return model_->tick(); }

int *s21::Controller::map() { return model_->map(); }

int s21::Controller::lvl() { return model_->lvl(); }

int s21::Controller::score() { return model_->score(); }

int s21::Controller::highScore() { return model_->highScore(); }

void s21::Controller::left() { model_->left(); }

void s21::Controller::right() { model_->right(); }

void s21::Controller::up() { model_->up(); }

void s21::Controller::down() { model_->down(); }

void s21::Controller::non() { model_->non(); }

void s21::Controller::again(bool status) { model_->again(status); }

bool s21::Controller::fail() { return model_->fail(); }

bool s21::Controller::end() { return !model_->end(); }

bool s21::Controller::win() { return model_->win(); }

int s21::Controller::speed() { return model_->speed(); }

int s21::Controller::nextTetrCol(int tetr, int ori, int cel) {
  Tlocation temple = getTetr(tetr, ori, cel);
  return temple.col;
}

int s21::Controller::nextTetrRow(int tetr, int ori, int cel) {
  Tlocation temple = getTetr(tetr, ori, cel);
  return temple.row;
}

void s21::Controller::left_t() { model_->left_t(); }

void s21::Controller::right_t() { model_->right_t(); }

void s21::Controller::up_t() { model_->up_t(); }

void s21::Controller::down_t() { model_->down_t(); }

void s21::Controller::drop_t() { model_->drop_t(); }

void s21::Controller::again_t(bool status) { model_->again_t(status); }

void s21::Controller::tick_t() { model_->tick_t(); }

int *s21::Controller::map_t() { return model_->map_t(); }

int s21::Controller::lvl_t() { return model_->lvl_t(); }

int s21::Controller::score_t() { return model_->score_t(); }

int s21::Controller::highScore_t() { return model_->highScore_t(); }

int s21::Controller::nextTetrType() { return model_->nextTetrType(); }
int s21::Controller::nextTetrOrint() { return model_->nextTetrOrint(); }

bool s21::Controller::fail_t() { return model_->fail_t(); }