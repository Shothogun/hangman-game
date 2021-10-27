#include <ncurses.h>
#include <iostream>
#include <string.h>
#include "../include/start.hpp"
#include "../include/game.hpp"

int main()
{
	hangman::Game *g = new hangman::Game();

	hangman::start_interface(g);

	delete g;

	return 0;
}