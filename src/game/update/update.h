#ifndef UPDATE_H
#define UPDATE_H

#include "../game.h"

typedef enum {
  GAME_STATUS_PLAYING,
  GAME_STATUS_END,
} GameStatus;

GameStatus game_update(GameState *game_state);

#endif // UPDATE_H
