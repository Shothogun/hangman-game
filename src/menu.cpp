#include "menu.hpp"

using namespace std;

Box::Box(int starty, int startx, int height, int width) {
	this->startx = startx;
	this->starty = starty;
	this->height = height;
	this->width = width;
	this->win = newwin(height+2, width+2, starty-1, startx-1);
}

Box::~Box(){
	werase(this->win);
	wrefresh(this->win);
	delwin(this->win);
}

void Box::write_button(string str, int line) {
	if (line < this->height){
		if (str.size() > uint(this->width)){
			str.resize(this->width);
		}
		mvwprintw(this->win, line+1, int(this->width/2 - str.size()/2)+1, str.c_str());
	}
	wrefresh(this->win);
}

void Box::create_border() {
	box(this->win, 0, 0);
	wrefresh(this->win);
}

int Box::isThisButton(int x, int y) {
	if (x >= this->startx && x <= this->startx + this->width && y >= this->starty && y <= this->starty + this->height){
		return 1;
	}
	else return 0;
}

int initial_menu(WinData main_box_data){
	int separation;
	int ch, next_page = 0;
	int n_choices = 3;

	MEVENT event;

	separation = int(main_box_data.width/n_choices) + 1;

	Box text (5 + main_box_data.starty, main_box_data.startx + 1, 2, main_box_data.width - 2);
	wattron(text.win, A_BOLD|A_UNDERLINE);
	text.write_button("Bem-vindo ao jogo da forca!", 0);

	//write_menu (menu, separation, main_box_data);
	Box b1 (15 + main_box_data.starty, int(separation/10) + main_box_data.startx, 2, int(separation*4/5));
	b1.create_border();
	b1.write_button("Novo jogo", 0);
	b1.write_button("(1)", 1);
	Box b2 (15 + main_box_data.starty, int(11*separation/10) + main_box_data.startx, 2, int(separation*4/5));
	b2.create_border();
	b2.write_button("Ranking", 0);
	b2.write_button("(2)", 1);
	Box b3 (15 + main_box_data.starty, int(21*separation/10) + main_box_data.startx, 2, int(separation*4/5));
	b3.create_border();
	b3.write_button("Adicao de palavras", 0);
	b3.write_button("(3)", 1);
	Box bexit (3 + main_box_data.starty, main_box_data.width - 10 + main_box_data.startx, 1, 6);
	bexit.create_border();
	bexit.write_button("Sair", 0);

	mousemask(ALL_MOUSE_EVENTS, NULL);

	ch = getch();
	
	while(ch != 27){
		ch = getch();
		switch(ch){
			case '1':
				mvwprintw(stdscr, 0, 0, "Novo jogo");
				next_page = 1;
				ch = 27;
				break;
			case '2':
				mvwprintw(stdscr, 0, 0, "Ranking");
				next_page = 2;
				ch = 27;
				break;
			case '3':
				mvwprintw(stdscr, 0, 0, "Adicao de palavras");
				next_page = 3;
				ch = 27;
				break;
			case KEY_MOUSE:
				if(getmouse(&event) == OK){
					if(event.bstate & BUTTON1_PRESSED || event.bstate & BUTTON1_CLICKED){
						if (b1.isThisButton(event.x, event.y)){
							next_page = 1;
							ch = 27;
						}
						else if (b2.isThisButton(event.x, event.y)){
							next_page = 2;
							ch = 27;
						}
						else if(b3.isThisButton(event.x, event.y)){
							next_page = 3;
							ch = 27;
						}
						else if (bexit.isThisButton(event.x, event.y)){
							next_page = 27;
							ch = 27;
						}
					}
				}
				break;
			case 27:
				next_page = 27;
				break;
			default:
				break;
		}
	}

	return next_page;
}

int new_game_menu(WinData main_box_data, int *p_n_players, int* p_n_rounds, int* p_n_lifes, string* names){
	int next_page = 1;
	char ch;
	int n;
	char str[80];

	echo();
	//nocbreak();

	getstr(str);
	mvwprintw(stdscr, 0, 0, to_string(n).c_str());
	while(ch != 27){
		ch = getch();
	}
	return ch;
}

int start_interface(){
	int page = 0;
	int number_players = 1, number_rounds = 1, number_lifes = 1;
	string *names;
	WINDOW *main_box;
	WinData main_box_data;

	main_box_data.height = 20;
	main_box_data.width = 80;
	main_box_data.startx = 8;
	main_box_data.starty = 3;

	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(false); //Seta do mouse?
	refresh();

	main_box = newwin(main_box_data.height+2, main_box_data.width+2, main_box_data.starty-1, main_box_data.startx-1);
	box(main_box, 0 , 0);
	wrefresh(main_box);

	while(page != 27){
		switch(page){
			case 0:
				page = initial_menu(main_box_data);
				break;
			case 1:
				page = new_game_menu(main_box_data, &number_players, &number_rounds, &number_lifes, names);
				break;
			default:
				getch();
				page = 27;
				break;
		}
	}

	delwin(main_box);

	return page;
}