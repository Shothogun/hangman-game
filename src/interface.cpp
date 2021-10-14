#include "../include/interface.hpp"

using namespace std;

namespace hangman {

	int start_interface(Game* g){
		int page = MAIN;
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

		while(page != EXIT){
			GameInterface* game_interface = new GameInterface(main_box_data);
			switch(page){
				case MAIN:
					page = initial_menu(main_box_data);
					break;
				case GAME:
					page = new_game_menu(main_box_data, &number_players, &number_rounds, &number_lifes, &names);
					if(number_players <= 0) number_players = 1;
					if(number_rounds <= 0) number_rounds = 1;
					if(number_lifes <= 0) number_lifes = 1;

					g->setPlayerAmount(number_players);
					g->RoundPlayersInit();
					g->setPlayersName(names);
					g->setPlayersLife(number_lifes);

					g->Round(game_interface);

					//while(page != EXIT){
					//	page = getch();
					//}

					break;
				case NWORD:
					page = new_word_menu(main_box_data);
					break;
				default:
					getch();
					page = EXIT;
					break;
			}
			delete game_interface;
		}

		delwin(main_box);
		endwin();

		return page;
	}
}