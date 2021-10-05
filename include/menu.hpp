#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "game.hpp"

using namespace std;

namespace hangman {

	struct WinData {
		int startx, starty;
		int height, width;
	};

	class Box {
		public:
			WINDOW *win;
			int startx, starty;
			int height, width;
			void create_border();
			void write_center(string str, int line);
			void write_begin(string str, int line);
			void refresh() {wrefresh(this->win);};
			void erase() {werase(this->win);};
			int isThisButton(int x, int y);
			string read_str(int line, int position);
			Box(int starty, int startx, int height, int width);
			~Box();
	};

	int initial_menu(WINDOW *main_box, WinData main_box_data);

	int start_interface(Game* g);
}
#endif