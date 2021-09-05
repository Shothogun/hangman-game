#include <ncurses.h>
#include <iostream>
#include "menu.hpp"

int main()
{
  int key_command;
  
  while (1)
  {
    initscr();
    printw("Hello World !!!");
    refresh();
    key_command = getch();
    initial_menu();

    // ESC Key
    if(key_command == 27){
      break;
    }
  }
  endwin();

  return 0;
}