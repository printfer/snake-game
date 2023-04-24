#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

int custom_menu_with_highlight_and_offset(WINDOW *win, char **options, int num_options, int current_highlight, int offset);
int custom_menu_with_highlight(WINDOW *win, char **options, int num_options, int current_highlight);
int custom_menu_with_offset(WINDOW *win, char **options, int num_options, int current_highlight);
int custom_menu(WINDOW *win, char **options, int num_options);

#endif // MENU_H
