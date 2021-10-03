#include "menu.hpp"

using namespace std;

class Button {
	public:
		WINDOW *win;
		int startx, starty;
		int height, width;
		void create_border();
		void write_button(string str, int line);
		void refresh() {wrefresh(this->win);};
		void erase() {werase(this->win);};
		Button(int starty, int startx, int height, int width);
		~Button() {delwin(this->win);};
};

Button::Button(int starty, int startx, int height, int width) {
	this->startx = startx;
	this->starty = starty;
	this->height = height;
	this->width = width;
	win = newwin(height+2, width+2, starty-1, startx-1);
}

void Button::write_button(string str, int line) {
	if (line < this->height){
		if (str.size() > uint(this->width)){
			str.resize(this->width);
		}
		mvwprintw(this->win, line+1, int(this->width/2 - str.size()/2)+1, str.c_str());
	}
	wrefresh(this->win);
}

void Button::create_border() {
	box(this->win, 0, 0);
	wrefresh(this->win);
};

struct WinData {
	int startx, starty;
	int height, width;
};

/*void write_menu (WINDOW* menu, int separation, WinData main_box_data){

	//mvwprintw(menu, 15, int(separation/2)-4, "Novo jogo");
	mvwprintw(menu, 15, int(3*separation/2)-3, "Ranking");
	mvwprintw(menu, 15, int(5*separation/2)-8, "Adicao de palavras");
	mvwprintw(menu, 16, int(separation/2)-1, "(1)");
	mvwprintw(menu, 16, int(3*separation/2)-1, "(2)");
	mvwprintw(menu, 16, int(5*separation/2)-1, "(3)");
	mvwprintw(menu, 1, 74, "Sair");
	wrefresh(menu);
}*/

int initial_menu(){
	WINDOW *main_box;
	WinData main_box_data;
	int separation;
	int ch;
	int n_choices = 3;

	MEVENT event;

	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(false); //Seta do mouse?
	refresh();

	main_box_data.height = 20;
	main_box_data.width = 80;
	main_box_data.startx = 8;
	main_box_data.starty = 3;
	separation = int(main_box_data.width/n_choices);

	main_box = newwin(main_box_data.height+2, main_box_data.width+2, main_box_data.starty-1, main_box_data.startx-1);
	box(main_box, 0 , 0);
	wrefresh(main_box);

	//write_menu (menu, separation, main_box_data);
	Button novo_jogo(15 + main_box_data.starty, int(separation/10) + main_box_data.startx, 2, int(separation*4/5));
	novo_jogo.create_border();
	novo_jogo.write_button("Novo jogo", 0);
	novo_jogo.write_button("(1)", 1);
	Button ranking(15 + main_box_data.starty, int(11*separation/10) + main_box_data.startx, 2, int(separation*4/5));
	ranking.create_border();
	ranking.write_button("Ranking", 0);
	ranking.write_button("(2)", 1);
	Button add(15 + main_box_data.starty, int(21*separation/10) + main_box_data.startx, 2, int(separation*4/5));
	add.create_border();
	add.write_button("Adicao de palavras", 0);
	add.write_button("(3)", 1);

	mousemask(ALL_MOUSE_EVENTS, NULL);

	ch = getch();
	
	while(ch != 27){
		ch = getch();
		switch(ch){
			case '1':
			  wrefresh(main_box);
				mvwprintw(stdscr, 0, 0, "Novo jogo");
				break;
			case '2':
				wrefresh(main_box);
				mvwprintw(stdscr, 0, 0, "Ranking");
				break;
			case '3':
				wrefresh(main_box);
				mvwprintw(stdscr, 0, 0, "Adicao de palavras");
				break;
			case '4':
				werase(main_box);
				wrefresh(main_box);
				break;
			case KEY_MOUSE:
				if(getmouse(&event) == OK){
					if(event.bstate & BUTTON1_PRESSED || event.bstate & BUTTON1_CLICKED){
						wrefresh(main_box);
						mvwprintw(stdscr, 0, 0, (to_string(event.x)+ ' ' + to_string(event.y) + ' ').c_str());
					}
				}
				break;
			default:
				break;
		}
	}
	delwin(main_box);

	return ch;
}