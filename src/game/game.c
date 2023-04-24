#include "game.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "input/input.h"
#include "render/render.h"
#include "update/update.h"

#include "../utils/menu/menu.h"

// Initialize the snake's memory with an initial capacity.
static void init_snake_memory(GameState *game_state) {
  game_state->snake_capacity = 100;
  game_state->snake = (Point *)malloc(game_state->snake_capacity * sizeof(Point));
}

// Initializes the game window
static void init_game_window(GameState *game_state) {
  // Calculate window sizes
  int info_window_height = 3;
  int game_window_height = LINES - info_window_height;

  // Create windows
  game_state->window.info = newwin(info_window_height, COLS, 0, 0);
  game_state->window.game = newwin(game_window_height, COLS, info_window_height, 0);
}

// Initializes the game state
static void init_game(GameState *game_state) {
  clear();
  init_game_window(game_state);
  init_snake_memory(game_state);

  timeout(500);

  srand(time(NULL));

  int game_window_height = getmaxy(game_state->window.game);
  int game_window_width = getmaxx(game_state->window.game);

  game_state->score = 0;
  game_state->snake_length = 1;
  game_state->snake[0].x = game_window_width / 2;
  game_state->snake[0].y = game_window_height / 2;
  game_state->food.x = rand() % (game_window_width - 4) + 2;
  game_state->food.y = rand() % (game_window_height - 4) + 2;
  game_state->direction = (Direction)(rand() % 4);
}

// Cleans up and closes the game window
static void end_game_window(GameState *game_state) {
  delwin(game_state->window.info);
  delwin(game_state->window.game);
}

// Shows the game over screen
static bool show_game_over_screen(GameState *game_state) {
  char *options[] = {"Restart Game", "Return to Menu"};
  int num_options = sizeof(options) / sizeof(options[0]);

  werase(game_state->window.game);

  // Print game over message
  int score_digits = game_state->score > 0 ? (int)log10(game_state->score) + 1 : 1;
  int game_window_height = getmaxy(game_state->window.game);
  int game_window_width = getmaxx(game_state->window.game);
  int start_y = game_window_height / 2 - 3;
  int start_x = game_window_width / 2 - 12 - (score_digits / 2);
  mvwprintw(game_state->window.game, start_y, start_x, "Game over! Final score: %d", game_state->score);

  // Print and get menu options
  int selected_option = custom_menu(game_state->window.game, options, num_options);

  return selected_option == 0;
}

// Main game loop
void game() {
  GameState game_state;
  GameStatus game_status = GAME_STATUS_PLAYING;

  while (1) { // Run the game loop indefinitely
    init_game(&game_state);
    game_render(&game_state);

    game_status = GAME_STATUS_PLAYING;
    while (game_status == GAME_STATUS_PLAYING) {
      game_input(&game_state);
      game_status = game_update(&game_state);
      game_render(&game_state);
    }

    // Display the game over screen and wait for the user to quit or restart
    bool restart = false;
    restart = show_game_over_screen(&game_state); // Display the game over screen

    // Free the snake's memory after the game loop
    free(game_state.snake);

    // End the game and clean up resources
    end_game_window(&game_state);

    // If the user didn't press 'r', exit the game loop
    if (!restart) {
      break;
    }
  }
}
