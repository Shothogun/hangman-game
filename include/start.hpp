#ifndef START_H
#define START_H

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "interfaces.hpp"
#include "game.hpp"
#include "file.hpp"

using namespace std;

namespace hangman{
	// Determine the size of the main frame and the sequence of the screens
	int start_interface(Game* g);
}

#endif