#include <gtest/gtest.h>

#include <iostream>

#include "../backend.h"

namespace {
TEST(Game, tick) {
  s21::Sgame game;
  game.tick();
  game.action(s21::LEFT);
  game.tick();
  game.action(s21::RIGHT);
  game.tick();
  game.action(s21::UP);
  game.tick();
  game.action(s21::DOWN);
  EXPECT_FALSE(game.getEnd());
}

TEST(Game, eat) {
  s21::Sgame game;
  game.tick();
  game.rmApple();
  game.tick();
  game.tick();

  game.tick();
  game.rmApple();
  game.action(s21::LEFT);
  game.tick();
  game.tick();

  game.tick();
  game.rmApple();
  game.action(s21::UP);
  game.tick();
  game.tick();

  game.tick();
  game.rmApple();
  game.action(s21::RIGHT);
  game.tick();
  game.tick();

  game.tick();
  game.rmApple();
  game.action(s21::NON);
  game.tick();
  game.tick();

  EXPECT_EQ(5, game.score());
  EXPECT_EQ(2, game.lvl());
  EXPECT_EQ(900, game.getSpeed());

  game.again(true);
  game.tick();
  EXPECT_EQ(5, game.highScore());
  EXPECT_EQ(1000, game.getSpeed());
  int *temple = game.arr();
  EXPECT_EQ(0, temple[0]);
}

TEST(Game, end) {
  s21::Sgame game;
  game.tick();
  game.action(s21::LEFT);
  while (!game.getFail()) {
    game.tick();
  }

  EXPECT_TRUE(game.getFail());

  game.again(true);
  game.tick();
  while (!game.getFail()) {
    game.tick();
  }
  EXPECT_TRUE(game.getFail());

  EXPECT_FALSE(game.getWin());

  game.again(false);
  EXPECT_TRUE(game.getEnd());
}

}  // namespace

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
