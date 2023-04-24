#include "screen.h"

#include <ncurses.h>
#include <string.h>

#include "../utils/menu/menu.h"

void init_screen() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
}

void end_screen() {
  // Clean up and close the library
  endwin();
}

// Print welcome screen with a default option
int screen_welcome(int from_option) {
  clear();

  // Define welcome options
  char *options[] = {"Start", "About", "Quit"};
  int num_options = sizeof(options) / sizeof(options[0]);

  // Print welcome messages
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  const char *snake_lines[] = {
      " _____             _        ",
      "/  ___|           | |       ",
      "\\ `--. _ __   __ _| | _____ ",
      " `--. \\ '_ \\ / _` | |/ / _ \\",
      "/\\__/ / | | | (_| |   <  __/",
      "\\____/|_| |_|\\__,_|_|\\_\\___|"};

  int start_y = (LINES - sizeof(snake_lines) / sizeof(snake_lines[0])) / 2 - 3;
  int start_x = (COLS - strlen(snake_lines[0])) / 2;

  attron(COLOR_PAIR(1));
  for (int i = 0; i < (int)(sizeof(snake_lines) / sizeof(snake_lines[0])); i++) {
    mvprintw(start_y + i, start_x, "%s", snake_lines[i]);
  }
  attroff(COLOR_PAIR(1));

  // Print and get menu options
  int selected_option = custom_menu_with_highlight_and_offset(stdscr, options, num_options, from_option, 3);

  return selected_option;
}

// Print about screen
void screen_about() {
  clear();

  char *options[] = {"Return"};
  int num_options = sizeof(options) / sizeof(options[0]);

  // Print about message
  const char *about_lines[] = {
      "--------------------------------------------------",
      " `snake` - https://github.com/printfer/snake-game",
      "--------------------------------------------------",
      "Snake is a modern implementation of the beloved",
      "classic using the ncurses library in C. Experience",
      "the addictive gameplay in a sleek terminal",
      "environment, controlled effortlessly with arrow",
      "keys or vim-like keys (h, j, k, l).",
      "--------------------------------------------------",
      "Copyright (c) 2023 printfer. All rights reserved.",
      "This is a free software licensed under the GPLv3.",
      "--------------------------------------------------",
  };

  int start_y = (LINES - sizeof(about_lines) / sizeof(about_lines[0])) / 2 - 2;
  int start_x = (COLS - strlen(about_lines[0])) / 2;

  for (int i = 0; i < (int)(sizeof(about_lines) / sizeof(about_lines[0])); i++) {
    mvprintw(start_y + i, start_x, "%s", about_lines[i]);
  }

  // Print menu options
  custom_menu_with_offset(stdscr, options, num_options, 5);
}
