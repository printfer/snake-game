#include "menu.h"

#include <stdarg.h>
#include <string.h>

// This function prints the menu options in the specified ncurses window.
// It highlights the option specified by current_highlight.
// Parameters:
//   - win: The ncurses window in which the menu options will be displayed.
//   - options: An array of strings representing the menu options.
//   - num_options: The number of options in the menu.
//   - current_highlight: The index of the option that should be highlighted.
//   - start_y: The starting y-coordinate for printing the options.
//   - start_x: The starting x-coordinate for printing the options.
static void print_options(WINDOW *win, char **options, int num_options, int current_highlight, int start_y, int start_x) {
  for (int i = 0; i < num_options; ++i) {
    if (i == current_highlight) {
      wattron(win, A_REVERSE);
      mvwprintw(win, start_y + i, start_x, "%s", options[i]);
      wattroff(win, A_REVERSE);
    } else {
      mvwprintw(win, start_y + i, start_x, "%s", options[i]);
    }
  }
  wrefresh(win);
}

// This function creates a menu with custom options, allows specifying a custom
// value for current_highlight, and provides an offset for the vertical position
// of the menu.
// Parameters:
//   - win: The ncurses window in which the menu will be displayed.
//   - options: An array of strings representing the menu options.
//   - num_options: The number of options in the menu.
//   - current_highlight: The index of the initially highlighted menu option.
//   - offset: The vertical offset for the menu position (positive values move the menu down, negative values move the menu up).
// Returns: The index of the selected menu option.
int custom_menu_with_highlight_and_offset(WINDOW *win, char **options, int num_options, int current_highlight, int offset) {

  // Calculate the center position
  int win_width, win_height;
  getmaxyx(win, win_height, win_width);
  int start_y = win_height / 2 - num_options / 2 + offset;
  int longest_option = 0;
  for (int i = 0; i < num_options; ++i) {
    int len = strlen(options[i]);
    if (len > longest_option) {
      longest_option = len;
    }
  }
  int start_x = (win_width - longest_option) / 2;

  // Print custom options
  print_options(win, options, num_options, current_highlight, start_y, start_x);

  int ch;
  while (1) {
    ch = getch();

    switch (ch) {
    case KEY_UP:
    case 'k': // Added 'k' for up
      current_highlight = (current_highlight - 1 + num_options) % num_options;
      break;
    case KEY_DOWN:
    case 'j': // Added 'j' for down
      current_highlight = (current_highlight + 1) % num_options;
      break;
    case ' ': // Space key
    case 10:  // Enter key
      return current_highlight;
    default:
      continue;
    }

    print_options(win, options, num_options, current_highlight, start_y, start_x);
  }
}

// This function creates a menu with custom options and handles user input.
// It allows specifying a custom value for current_highlight.
// Parameters:
//   - win: The ncurses window in which the menu will be displayed.
//   - options: An array of strings representing the menu options.
//   - num_options: The number of options in the menu.
//   - current_highlight: The index of the initially highlighted menu option.
// Returns: The index of the selected menu option.
int custom_menu_with_highlight(WINDOW *win, char **options, int num_options, int current_highlight) {
  int default_offset = 0;
  return custom_menu_with_highlight_and_offset(win, options, num_options, current_highlight, default_offset);
}

// This function creates a menu with custom options and provides an offset for
// the vertical position of the menu. It uses the default value for current_highlight.
// Parameters:
//   - win: The ncurses window in which the menu will be displayed.
//   - options: An array of strings representing the menu options.
//   - num_options: The number of options in the menu.
//   - offset: The vertical offset for the menu position (positive values move the menu down, negative values move the menu up).
// Returns: The index of the selected menu option.
int custom_menu_with_offset(WINDOW *win, char **options, int num_options, int offset) {
  int default_current_highlight = 0;
  return custom_menu_with_highlight_and_offset(win, options, num_options, default_current_highlight, offset);
}

// This function creates a menu with custom options and handles user input.
// It uses the default value for current_highlight.
// Parameters:
//   - win: The ncurses window in which the menu will be displayed.
//   - options: An array of strings representing the menu options.
//   - num_options: The number of options in the menu.
// Returns: The index of the selected menu option.
int custom_menu(WINDOW *win, char **options, int num_options) {
  int default_current_highlight = 0;
  int default_offset = 0;
  return custom_menu_with_highlight_and_offset(win, options, num_options, default_current_highlight, default_offset);
}
