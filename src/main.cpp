#include <ncurses.h>
#include <iostream>

int main()
{
  int key_command;
  
  while (1)
  {
    initscr();
    printw("Hello World !!!");
    refresh();
    key_command = getch();
    endwin();

    // ESC Key
    if(key_command == 27){
      break;
    }
  }

  return 0;
}