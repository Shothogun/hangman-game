#include "../include/start.hpp"

using namespace std;

namespace hangman {

	// Determine the size of the main frame and the sequence of the screens
	int start_interface(Game* g){
		int page = MAIN;
		int number_players = 1, number_rounds = 1, number_lifes = 1;
		vector<string> names;
		WINDOW *main_box;

		// Main frame size and position
		WinData main_box_data;
		main_box_data.height = 20;
		main_box_data.width = 80;
		main_box_data.startx = 8;
		main_box_data.starty = 3;

		// Initial ncurses procedures
		initscr();
		cbreak();
		keypad(stdscr, TRUE);
		noecho();
		curs_set(false); //Seta do mouse?
		refresh();

		// Main frame
		main_box = newwin(main_box_data.height+2, main_box_data.width+2, main_box_data.starty-1, main_box_data.startx-1);
		box(main_box, 0 , 0);
		wrefresh(main_box);

		// Screens sequency behaviour
		while(page != EXIT){
			GameInterface* game_interface = new GameInterface(main_box_data);
			switch(page){
				case MAIN:
					page = initial_menu(main_box_data);
					break;
				case GAME:
					new_game_menu(main_box_data, &number_players, &number_rounds, &number_lifes, &names);
					if(number_players <= 0) number_players = 1;
					if(number_rounds <= 0) number_rounds = 1;
					if(number_lifes <= 0) number_lifes = 1;

					g->setPlayerAmount(number_players);
					g->RoundPlayersInit();
					g->setPlayersName(names);
					g->setPlayersLife(number_lifes);
					g->Round(game_interface);

					game_interface->erase_all();

					round_winner_screen(main_box_data, "Giordano");

					game_winner_screen(main_box_data, "Giordano");


					break;
				case RANK:
					page = ranking_menu(main_box_data);
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