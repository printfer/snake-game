#include "game/game.h"
#include "screen/screen.h"

int main() {
  // Initialize the game screen
  init_screen();

  // Check terminal size
  int screen_height, screen_width;
  getmaxyx(stdscr, screen_height, screen_width);

  // Validate terminal dimensions
  if (screen_height < MIN_SCREEN_HEIGHT || screen_width < MIN_SCREEN_WIDTH) {
    // Close the ncurses window
    endwin();
    // Print an error message and exit if the terminal size is too small
    printf("Terminal size is too small. Minimum size: %dx%d\n", MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT);
    return 1;
  }

  // Main loop variable for handling user input
  int welcome_option = 0;

  // Main loop for the game
  while (1) {
    // Display the welcome screen and get user input
    welcome_option = screen_welcome(welcome_option);

    // Start the game
    if (welcome_option == 0) {
      game();
    }

    // Display the about screen
    if (welcome_option == 1) {
      screen_about();
    }

    // Exit the game
    if (welcome_option == 2) {
      end_screen();
      return 0;
    }
  }

  // Close the game screen and exit
  end_screen();
  return 0;
}
