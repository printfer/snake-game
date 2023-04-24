#include <stdlib.h>

#include "update.h"

// Helper function to check if a point is within the snake
int is_point_in_snake(Point p, Point *snake, int snake_length) {
  for (int i = 0; i < snake_length; i++) {
    if (p.x == snake[i].x && p.y == snake[i].y) {
      return 1;
    }
  }
  return 0;
}

// Generates a random point on the game window
Point generate_random_point(int game_window_width, int game_window_height) {
  Point p;
  p.x = rand() % (game_window_width - 4) + 2;
  p.y = rand() % (game_window_height - 4) + 2;
  return p;
}

// Updates the snake's position based on its current direction
void update_snake_position(GameState *game_state) {
  // Update the snake's body
  for (int i = game_state->snake_length - 1; i > 0; i--) {
    game_state->snake[i] = game_state->snake[i - 1];
  }

  // Update the snake's head based on the current direction
  switch (game_state->direction) {
  case UP:
    game_state->snake[0].y -= 1;
    break;
  case DOWN:
    game_state->snake[0].y += 1;
    break;
  case LEFT:
    game_state->snake[0].x -= 1;
    break;
  case RIGHT:
    game_state->snake[0].x += 1;
    break;
  }
}

// Checks if the snake has collided with the game window boundaries
int has_collision_with_boundaries(GameState *game_state, int game_window_width, int game_window_height) {
  return game_state->snake[0].x < 1 || game_state->snake[0].x >= game_window_width - 1 ||
         game_state->snake[0].y < 1 || game_state->snake[0].y >= game_window_height - 1;
}

// Checks if the snake has collided with its body
int has_collision_with_body(GameState *game_state) {
  for (int i = 1; i < game_state->snake_length; i++) {
    if (game_state->snake[0].x == game_state->snake[i].x &&
        game_state->snake[0].y == game_state->snake[i].y) {
      return 1;
    }
  }
  return 0;
}

// Resizes the snake's memory
static void resize_snake_memory(GameState *game_state) {
  game_state->snake_capacity *= 2;
  game_state->snake = (Point *)realloc(game_state->snake, game_state->snake_capacity * sizeof(Point));
}

// Increase game speed by reducing the timeout interval
static void increase_game_speed(int snake_length) {
  const int speed_increment = 10;
  const int min_timeout_value = 400;
  const int initial_timeout_value = 500;

  int speed_increase = snake_length / 10;
  int timeout_value = initial_timeout_value - (speed_increase * speed_increment);

  timeout_value = (timeout_value < min_timeout_value) ? min_timeout_value : timeout_value;
  timeout(timeout_value);
}

// Updates the food position and the snake's state when the snake eats the food
void update_food_and_snake(GameState *game_state, int game_window_width, int game_window_height) {
  if (game_state->snake[0].x == game_state->food.x && game_state->snake[0].y == game_state->food.y) {
    game_state->score += 10;
    game_state->snake_length++;

    // Resize the snake's memory when the snake's length reaches the current
    // capacity.
    if (game_state->snake_length == game_state->snake_capacity) {
      resize_snake_memory(game_state);
    }

    // Adjust snake speed
    increase_game_speed(game_state->snake_length);

    // Generate new food location that is not within the snake
    do {
      game_state->food = generate_random_point(game_window_width, game_window_height);
    } while (is_point_in_snake(game_state->food, game_state->snake, game_state->snake_length));
  }
}

GameStatus game_update(GameState *game_state) {
  int game_window_height;
  int game_window_width;
  getmaxyx(game_state->window.game, game_window_height, game_window_width);

  update_snake_position(game_state);

  if (has_collision_with_boundaries(game_state, game_window_width, game_window_height)) {
    return GAME_STATUS_END;
  }

  update_food_and_snake(game_state, game_window_width, game_window_height);

  if (has_collision_with_body(game_state)) {
    return GAME_STATUS_END;
  }

  return GAME_STATUS_PLAYING;
}
