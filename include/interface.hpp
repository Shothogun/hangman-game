#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "menu.hpp"
#include "game.hpp"
#include "file.hpp"

using namespace std;

namespace hangman{
	int start_interface(Game* g);
}

#endif