#include <check.h>
#include <stdbool.h>
#include <stdio.h>

#include "../back.h"

START_TEST(test_serv) {
  Tgame game = gameInit();
  game.score = 5500;
  ticker(&game);
  ck_assert_int_eq(game.highScore, 5500);
  ticker(&game);
  newGame(&game);
  ck_assert_int_eq(game.highScore, 5500);

  while (!gameOver(&game)) {
    moving(&game, TDROP);
    ticker(&game);
  }
  gameDelete(&game);
}
END_TEST

START_TEST(test_block) {
  Tgame game = gameInit();
  Tmove move = TUP;
  moving(&game, move);
  ticker(&game);
  while (!gameOver(&game)) {
    moving(&game, TDROP);
    ticker(&game);
  }

  newGame(&game);
  move = TLEFT;
  moving(&game, move);
  ticker(&game);
  while (!gameOver(&game)) {
    moving(&game, TDROP);
    ticker(&game);
  }

  newGame(&game);
  move = TRIGHT;
  moving(&game, move);
  ticker(&game);
  while (!gameOver(&game)) {
    moving(&game, TDROP);
    ticker(&game);
  }

  newGame(&game);
  move = TDROP;
  moving(&game, move);
  ticker(&game);
  while (!gameOver(&game)) {
    moving(&game, TDROP);
    ticker(&game);
  }

  newGame(&game);
  move = TCOUNTER;
  moving(&game, move);
  ticker(&game);
  move = TDOWN;
  moving(&game, move);
  ticker(&game);
  while (!gameOver(&game)) {
    for (int i = 0; i < 2; i++) {
      moving(&game, TDROP);
      ticker(&game);
      game.gravityTicks = 0;
    }
  }

  move = TPAUSE;
  moving(&game, move);
  ticker(&game);
  ck_assert_int_eq(AGAIN, 1);
  gameDelete(&game);
}
END_TEST

START_TEST(test_lines) {
  Tgame game = gameInit();
  Tmove move = TNONE;
  moving(&game, move);
  ticker(&game);
  for (int i = 189; i < 200; i++) {
    game.field[i] = 1;
  }
  moving(&game, move);
  ticker(&game);
  ck_assert_int_eq(game.score, 100);
  gameDelete(&game);
}
END_TEST

Suite *back() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("back func");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_serv);
  tcase_add_test(tc_core, test_block);
  tcase_add_test(tc_core, test_lines);
  suite_add_tcase(s, tc_core);

  return s;
}

int test_backend() {
  int no_failed = 0;

  Suite *s;
  SRunner *runner;

  s = back();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return no_failed;
}

int main() {
  int no_failed = 0;

  no_failed |= test_backend();

  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
