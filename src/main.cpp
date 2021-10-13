#include <ncurses.h>
#include <iostream>
#include "interface.hpp"
#include <string.h>
#include "game.hpp"

int main()
{
	hangman::Game *g = new hangman::Game();

	std::vector<std::string> names;

	names.push_back("Goku");
	names.push_back("Rogerio Ceni");
	names.push_back("Joel Santana");

	hangman::start_interface(g);

	delete g;

	return 0;
}