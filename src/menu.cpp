#include "menu.hpp"

using namespace std;

int initial_menu(){
	WINDOW *text_box;
	int height, width, startx, starty, separation;
	int ch;	

	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(false); //Seta do mouse?
	refresh();

	height = 20;
	width = 80;
	startx = 8;
	starty = 3;
	separation = int(width/3);

	text_box = newwin(height, width, starty, startx);
	box(text_box, 0 , 0);

	mvwprintw(text_box, 4, int(separation/2)-4, "Novo jogo");
	mvwprintw(text_box, 4, int(3*separation/2)-3, "Ranking");
	mvwprintw(text_box, 4, int(5*separation/2)-8, "Adicao de palavras");
	mvwprintw(text_box, 5, int(separation/2)-1, "(1)");
	mvwprintw(text_box, 5, int(3*separation/2)-1, "(2)");
	mvwprintw(text_box, 5, int(5*separation/2)-1, "(3)");
	wrefresh(text_box);

	ch = getch();
	
	while(ch != 27){
		switch(ch){
			case '1':
			  wrefresh(text_box);
				mvwprintw(stdscr, 0, 0, "Novo jogo");
				ch = getch();
				break;
			case '2':
				wrefresh(text_box);
				mvwprintw(stdscr, 0, 0, "Ranking");
				ch = getch();
				break;
			case '3':
				wrefresh(text_box);
				mvwprintw(stdscr, 0, 0, "Adicao de palavras");
				ch = getch();
				break;
			case '4':
				werase(text_box);
				wrefresh(text_box);
				ch = getch();
				break;
			default:
				ch = getch();
				break;
		}
	}
	delwin(text_box);

	return ch;
}