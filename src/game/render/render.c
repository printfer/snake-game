#include <math.h>

#include "render.h"

// Draws the snake on the game window.
static void draw_snake(GameState *game_state) {
  for (int i = 0; i < game_state->snake_length; i++) {
    mvwprintw(game_state->window.game, game_state->snake[i].y, game_state->snake[i].x, "O");
  }
}

// Draws the food on the game window.
static void draw_food(GameState *game_state) {
  mvwprintw(game_state->window.game, game_state->food.y, game_state->food.x, "*");
}

// Draws the game name and score on the info window.
static void draw_score(GameState *game_state) {
  int margin = 1;
  int max_x = getmaxx(game_state->window.info);

  // Calculate the number of digits in the score and the position for
  // displaying the score.
  int score_digits = game_state->score > 0 ? (int)log10(game_state->score) + 1 : 1;
  int score_length = 7 + score_digits + margin; // 7 characters for "score: " + the number of digits in the score
  int right_position = max_x - score_length - 1;

  // Display the game name and score.
  mvwprintw(game_state->window.info, 1, 1 + margin, "Snake Game");
  mvwprintw(game_state->window.info, 1, right_position, "score: %d", game_state->score);
}

// Renders the game by updating the game and info windows.
void game_render(GameState *game_state) {
  // Clear the windows.
  werase(game_state->window.info);
  werase(game_state->window.game);

  // Draw the game elements.
  draw_food(game_state);
  draw_snake(game_state);
  draw_score(game_state);

  // Draw the borders.
  box(game_state->window.info, 0, 0);
  box(game_state->window.game, 0, 0);

  // Refresh the windows to display the updates.
  wrefresh(game_state->window.info);
  wrefresh(game_state->window.game);
}
