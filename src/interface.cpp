#include "interface.hpp"

using namespace std;

namespace hangman {

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

		while(page != 27){
			GameInterface* game_interface = new GameInterface(main_box_data);
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

					g->Round(game_interface);

					/*game_interface.display_player("Giordano", 5);
					game_interface.display_cur_word("_______");
					game_interface.display_buttons();
					game_interface.wait_buttons();
					game_interface.erase_buttons();
					game_interface.guess_letter();
					game_interface.guess_word();
					game_interface.display_message("Aqui está você, o perdedor HAHA");
					getch();
					game_interface.erase_guess();
					game_interface.erase_message();*/



					while(page != 27){
						page = getch();
					}

					break;
				default:
					getch();
					page = 27;
					break;
			}
			delete game_interface;
		}

		delwin(main_box);
		endwin();

		return page;
	}
}