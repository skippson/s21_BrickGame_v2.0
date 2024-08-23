#include "../back.h"

void moving(Tgame *game, Tmove move) {
  switch (move) {
    case TLEFT:
      moveX(game, -1);
      break;
    case TRIGHT:
      moveX(game, 1);
      break;
    case TDROP:
      moveDrop(game);
      break;
    case TDOWN:
      moveDown(game);
      break;
    case TUP:
      moveRotate(game, 1);
      break;
    case TCOUNTER:
      moveRotate(game, -1);
      break;
    default:
      break;
  }
}

void moveX(Tgame *game, int place) {
  rmTetramino(game, game->falling);
  game->falling->loc.col += place;
  if (!checkMovesTetramino(game, game->falling)) {
    game->falling->loc.col -= place;
  }
  putTetramino(game, game->falling);
}

void moveDown(Tgame *game) {
  rmTetramino(game, game->falling);
  game->falling->loc.row++;
  if (!checkMovesTetramino(game, game->falling)) {
    game->falling->loc.row--;
  }
  putTetramino(game, game->falling);
  game->gravityTicks = getGravity(game->speed);
}

void moveDrop(Tgame *game) {
  rmTetramino(game, game->falling);
  while (checkMovesTetramino(game, game->falling)) {
    game->falling->loc.row++;
  }
  game->falling->loc.row--;
  putTetramino(game, game->falling);
  newFalling(game);
}

void moveRotate(Tgame *game, int orint) {
  rmTetramino(game, game->falling);
  while (1) {
    game->falling->orintation = (game->falling->orintation + orint) % ORI;

    if (checkMovesTetramino(game, game->falling)) break;

    game->falling->loc.col--;
    if (checkMovesTetramino(game, game->falling)) break;

    game->falling->loc.col += 2;
    if (checkMovesTetramino(game, game->falling)) break;

    game->falling->loc.col--;
  }

  putTetramino(game, game->falling);
}