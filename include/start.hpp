#ifndef START_H
#define START_H

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "interfaces.hpp"
#include "game.hpp"

using namespace std;

namespace hangman{
	int start_interface(Game* g);
}

#endif