#include <ncurses.h>
#include <iostream>
#include "menu.hpp"

int main()
{
  int key_command;
  initscr();
  printw("Hello World !!!");
  while (1)
  {
    refresh();
    key_command = initial_menu(); // COLS e LINES iniciadas após initscr()

    // ESC Key
    if(key_command == 27){
      break;
    }
  }
  endwin();

  return 0;
}