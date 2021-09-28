#include <ncurses.h>
#include <iostream>
#include <string.h>
#include "game.hpp"

int main(int argc, char *argv[])
{
	int key_command;
	char msg[] = "Just a string";
	int row, col;

	hangman::Game *g = new hangman::Game();

	std::vector<std::string> names;

	names.push_back("Goku");
	names.push_back("Rogerio Ceni");
	names.push_back("Joel Santana");

	g->setPlayerAmount(3);
	g->RoundPlayersInit();
	g->setPlayersName(names);
	g->setPlayersLife();
	g->Round();

	//   while (1)
	//   {
	//     initscr();

	//     getmaxyx(stdscr, row, col);
	//     mvprintw(row / 2, (col - strlen(msg)) / 2, "%s", msg);
	//     mvprintw(row - 2, 0, "This screen has %d rows and %d columns\n", row, col);
	//     printw("Try resizing your window(if possible) and then run this program again");
	//     refresh();
	//     key_command = getch();

	//     endwin();

	//     // ESC Key
	//     if (key_command == 27)
	//     {
	//       break;
	//     }
	//   }

	return 0;
}