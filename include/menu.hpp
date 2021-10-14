#ifndef MENU_H
#define MENU_H

#define MAIN 0
#define GAME 1
#define RANK 2
#define NWORD 3
#define EXIT 27

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <limits>
#include "file.hpp"

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
			char read_char(int line, int position);
			Box(int starty, int startx, int height, int width);
			~Box();
	};

	class GameInterface {
		public:
			int word_max_size = 20;
			Box *current_player;
			Box *cur_word;
			Box *button_word;
			Box *button_letter;
			Box *guess;
			Box *msg;
			void display_player(string name, int life);
			void display_cur_word (string word);
			void display_buttons();
			void erase_buttons();
			int wait_buttons();
			string guess_word();
			char guess_letter();
			void erase_guess();
			void display_message(string msg);
			void erase_message();
			GameInterface(WinData main_box_data);
			GameInterface(WinData main_box_data, int word_max_size);
			~GameInterface();

		private:
			void initialization(WinData main_box_data);
			
	};

	int initial_menu(WinData main_box_data);

	void new_game_menu(WinData main_box_data, int *p_n_players, int* p_n_rounds, int* p_n_lifes, vector<string>* names);

	int new_word_menu(WinData main_box_data);

	int ranking_menu(WinData main_box_data);

	int get_first_rank(vector<pair<string, string>> rankings);
}
#endif