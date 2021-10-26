#include "../include/start.hpp"

using namespace std;

namespace hangman {

	// Determine the size of the main frame and the sequence of the screens
	int start_interface(Game* g){
		int page = MAIN;
		int number_players = 1, number_rounds = 1, number_lifes = 1;
		vector<pair<string, string>> ranking = readRanking("src/ranking.txt");
		vector<pair<int, string>> rankingPoints;
		vector<string> names;
		WINDOW *main_box;
		string winner_name;
		int winner_points;

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
					names.clear();
					new_game_menu(main_box_data, &number_players, &number_rounds, &number_lifes, &names);
					if(number_players <= 0) number_players = 1;
					if(number_rounds <= 0) number_rounds = 1;
					if(number_lifes <= 0) number_lifes = 1;
					g->setPlayerAmount(number_players);
					g->RoundPlayersInit();
					g->setPlayersName(names);

					while(number_rounds--){
						g->RoundPlayersSoftReset(number_lifes);
						g->Round(game_interface);
						rankingPoints.clear();

						for(int i = 0; i < g->getPlayersAmount(); i++){
							rankingPoints.push_back(make_pair(g->getGamePlayers()[i]->getPoint(), g->getGamePlayers()[i]->getName()));
						}

						sort(rankingPoints.begin(), rankingPoints.end());

						winner_name = rankingPoints[rankingPoints.size()-1].second;
						winner_points = rankingPoints[rankingPoints.size()-1].first;

						// Round ending screens
						// If solo player lost the round
						if (g->getPlayersAmount() == 1 && g->getGamePlayers()[0]->getRoundLost()){
							round_loser_screen(main_box_data, winner_name);
						}
						else
							round_winner_screen(main_box_data, winner_name, winner_points);
					}

					rankingPoints.clear();
					for(uint i = 0; i < ranking.size(); i++){
						rankingPoints.push_back(make_pair(stoi(ranking[i].second), ranking[i].first));
					}
					for(int i = 0; i < g->getPlayersAmount(); i++){
						rankingPoints.push_back(make_pair(g->getGamePlayers()[i]->getPoint(), g->getGamePlayers()[i]->getName()));
					}

					sort(rankingPoints.begin(), rankingPoints.end());
					ranking.clear();
					for(uint i = 0 ; i < rankingPoints.size(); i++){
						ranking.push_back(make_pair(rankingPoints[rankingPoints.size() - 1 - i].second,
													to_string(rankingPoints[rankingPoints.size() - 1 - i].first)));
					}

					writeRanking("src/ranking.txt", ranking);

					game_interface->erase_all();

					page = game_winner_screen(main_box_data, winner_name, winner_points);

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