#include <ncurses.h>
#include <iostream>
#include <string>
#include<list>

using namespace std;

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
		void write_button(string str, int line);
		void refresh() {wrefresh(this->win);};
		void erase() {werase(this->win);};
		int isThisButton(int x, int y);
		Box(int starty, int startx, int height, int width);
		~Box();
};

int initial_menu(WINDOW *main_box, WinData main_box_data);

int start_interface();