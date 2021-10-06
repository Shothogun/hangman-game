#include "menu.hpp"

using namespace std;

namespace hangman {

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

	void Box::write_center(string str, int line) {
		if (line < this->height){
			if (str.size() > uint(this->width)){
				str.resize(this->width);
			}
			mvwprintw(this->win, line+1, int(this->width/2 - str.size()/2)+1, str.c_str());
		}
		wrefresh(this->win);
	}

	void Box::write_begin(string str, int line) {
		if (line < this->height){
			if (str.size() > uint(this->width)){
				str.resize(this->width);
			}
			mvwprintw(this->win, line+1, 1, str.c_str());
		}
		wrefresh(this->win);
	}

	string Box::read_str(int line, int position) {
		char s[80];

		echo();
		mvwgetstr(this->win, line + 1, position + 1, s);
		noecho();
		string str(s);

		return str;
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

	GameInterface::GameInterface(WinData main_box_data){
		int margin_y = 3, margin_x = 2;
		this->current_player = new Box(margin_y + main_box_data.starty, main_box_data.startx + margin_x, 2, main_box_data.width - 2*margin_x);
		//this->cur_word = new Box();
		//this->button_word = new Box();
		//this->button_letter = new Box();
		//this->guess = new Box();
		//this->msgs = new Box();
	}

	GameInterface::~GameInterface(){
		this->current_player->~Box();
		delete this->current_player;
		//delete this->cur_word;
		//delete this->button_word;
		//delete this->button_letter;
		//delete this->guess;
		//delete this->msgs;
	}

	void GameInterface::display_player(string name, int life){
		wattron(this->current_player->win, A_BOLD|A_UNDERLINE);
		this->current_player->write_center(name, 0);
		wattroff(this->current_player->win, A_UNDERLINE);
		this->current_player->write_center("Vidas: " + to_string(life), 1);
	}

	int initial_menu(WinData main_box_data){
		int separation;
		int ch, next_page = 0;
		int n_choices = 3;

		MEVENT event;

		separation = int(main_box_data.width/n_choices) + 1;

		Box text (5 + main_box_data.starty, main_box_data.startx + 1, 2, main_box_data.width - 2);
		wattron(text.win, A_BOLD|A_UNDERLINE);
		text.write_center("Bem-vindo ao jogo da forca!", 0);

		//write_menu (menu, separation, main_box_data);
		Box b1 (15 + main_box_data.starty, int(separation/10) + main_box_data.startx, 2, int(separation*4/5));
		b1.create_border();
		b1.write_center("Novo jogo", 0);
		b1.write_center("(1)", 1);
		Box b2 (15 + main_box_data.starty, int(11*separation/10) + main_box_data.startx, 2, int(separation*4/5));
		b2.create_border();
		b2.write_center("Ranking", 0);
		b2.write_center("(2)", 1);
		Box b3 (15 + main_box_data.starty, int(21*separation/10) + main_box_data.startx, 2, int(separation*4/5));
		b3.create_border();
		b3.write_center("Adicao de palavras", 0);
		b3.write_center("(3)", 1);
		Box bexit (3 + main_box_data.starty, main_box_data.width - 10 + main_box_data.startx, 1, 6);
		bexit.create_border();
		bexit.write_center("Sair", 0);

		mousemask(ALL_MOUSE_EVENTS, NULL);

		ch = 0;
		
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

	int new_game_menu(WinData main_box_data, int *p_n_players, int* p_n_rounds, int* p_n_lifes, vector<string>* names){
		char ch;
		int margin_y = 3, margin_x = 2, separation = 3;
		string str_q1 = "Escreva a quantidade de jogadores: ";
		string str_q2 = "Escreva a quantidade de rodadas: ";
		string str_q3 = "Escreva a quantidade de vidas por jogador: ";
		string str_q4 = "Escreva o nome do jogador ";

		Box q1 (margin_y + main_box_data.starty, margin_x + main_box_data.startx, 1, main_box_data.width - margin_y*2);
		q1.write_begin(str_q1, 0);
		*p_n_players = stoi(q1.read_str(0, str_q1.size()));
		Box q2 (q1.starty + q1.height + separation, margin_x + main_box_data.startx, 1, main_box_data.width - margin_y*2);
		q2.write_begin(str_q2, 0);
		*p_n_rounds = stoi(q2.read_str(0, str_q2.size()));
		Box q3 (q2.starty + q2.height + separation, margin_x + main_box_data.startx, 1, main_box_data.width - margin_y*2);
		q3.write_begin(str_q3, 0);
		*p_n_lifes = stoi(q3.read_str(0, str_q3.size()));

		Box q4 (q3.starty + q3.height + separation, margin_x + main_box_data.startx, 1, main_box_data.width - margin_y*2);

		for (int i = 0; i < *p_n_players; i++){
			q4.write_begin(str_q4 + to_string(i+1) + " : ", 0);
			names->push_back(q4.read_str(0, (str_q4 + to_string(i+1) + " : ").size()));
			q4.erase();
		}

		Box text (q4.starty + q4.height + separation-1, margin_x + main_box_data.startx, 1, main_box_data.width - margin_y*2);
		wattron(text.win, A_BOLD|A_UNDERLINE|A_STANDOUT);
		text.write_center("Tudo configurado! Clique ou aperte qualquer tecla para começar!", 0);

		mousemask(ALL_MOUSE_EVENTS, NULL);
		ch = getch();

		return ch;
	}

	int start_interface(Game* g){
		int page = 0;
		int number_players = 1, number_rounds = 1, number_lifes = 1;
		vector<string> names;
		WINDOW *main_box;

		WinData main_box_data;
		main_box_data.height = 20;
		main_box_data.width = 80;
		main_box_data.startx = 8;
		main_box_data.starty = 3;

		initscr();
		cbreak();
		keypad(stdscr, TRUE);
		noecho();
		curs_set(false); //Seta do mouse?
		refresh();

		main_box = newwin(main_box_data.height+2, main_box_data.width+2, main_box_data.starty-1, main_box_data.startx-1);
		box(main_box, 0 , 0);
		wrefresh(main_box);

		GameInterface game_interface (main_box_data);

		while(page != 27){
			switch(page){
				case 0:
					page = initial_menu(main_box_data);
					break;
				case 1:
					page = new_game_menu(main_box_data, &number_players, &number_rounds, &number_lifes, &names);
					if(number_players <= 0) number_players = 1;
					if(number_rounds <= 0) number_rounds = 1;
					if(number_lifes <= 0) number_lifes = 1;

					g->setPlayerAmount(number_players);
					g->RoundPlayersInit();
					g->setPlayersName(names);
					g->setPlayersLife(number_lifes);

					game_interface.display_player("Giordano", 5);

					while(page != 27){
						page = getch();
					}
					break;
				default:
					getch();
					page = 27;
					break;
			}
		}

		delwin(main_box);
		endwin();

		return page;
	}
}