#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

typedef struct {
  int x;
  int y;
} Point;

typedef enum { UP,
               DOWN,
               LEFT,
               RIGHT } Direction;

typedef struct {
  WINDOW *info;
  WINDOW *game;
} GameWindow;

typedef struct {
  int score;
  int snake_length;
  int snake_capacity; // Track allocated capacity for the snake
  Point *snake;
  Point food;
  Direction direction;
  GameWindow window;
} GameState;

void game();

#endif // GAME_H
