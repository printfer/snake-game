#include "input.h"

// Update the snake's direction based on user input
void update_snake_direction(GameState *game_state, int ch) {
  switch (ch) {
  case KEY_LEFT:
  case 'h': // Added 'h' for left
    if (game_state->direction != RIGHT) {
      game_state->direction = LEFT;
    }
    break;
  case KEY_RIGHT:
  case 'l': // Added 'l' for right
    if (game_state->direction != LEFT) {
      game_state->direction = RIGHT;
    }
    break;
  case KEY_UP:
  case 'k': // Added 'k' for up
    if (game_state->direction != DOWN) {
      game_state->direction = UP;
    }
    break;
  case KEY_DOWN:
  case 'j': // Added 'j' for down
    if (game_state->direction != UP) {
      game_state->direction = DOWN;
    }
    break;
  }
}

void game_input(GameState *game_state) {
  int ch = getch();

  // Update the snake's direction based on the input character
  update_snake_direction(game_state, ch);
}
