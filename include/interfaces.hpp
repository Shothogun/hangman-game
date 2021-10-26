#ifndef INTERFACES_H
#define INTERFACES_H

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

	// Structure to hold a window coordenates and dimensions
	struct WinData {
		int startx, starty;
		int height, width;
	};

	class Box {
		public:
			WINDOW *win; // Window pointer
			int startx, starty; // Box coordenates
			int height, width; // Box dimensions

			// Create a border arround the box
			void create_border();
			// Write text message in the center of the box in the line informed
			void write_center(string str, int line);
			// Write text message in the beginning of the box in the line informed
			void write_begin(string str, int line);
			void refresh() {wrefresh(this->win);}; // Refresh box content
			void erase() {werase(this->win);}; // Erase window box content (without refreshing)
			// Return if the general coordenates (x, y) are a part of this box
			int isThisButton(int x, int y);
			// Wait for a string input from the user in line and position (y, x) of the box
			string read_str(int line, int position);
			// Wait for a character input from the user in line and position (y, x) of the box
			char read_char(int line, int position);

			Box(int starty, int startx, int height, int width); // Box initializer
			~Box(); // Box destructor erase and delete window
	};

	class GameInterface {
		public:
			int word_max_size = 20; // Default word max size
			Box *current_player; // Box with player name and health
			Box *cur_word; // Box with current word status
			Box *button_word; // Box to proceed to guess the word
			Box *button_letter; // Box to proceed to guess a letter
			Box *guess; // Box to write the guess
			Box *msg; // Box to show the system message

			// Display player name and health
			void display_player(string name, int life, int points);
			// Display current state of the guessing word
			void display_cur_word (string word);
			// Display the two buttons
			void display_buttons();
			// Erase the two buttons
			void erase_buttons();
			// Wait the selection of a button
			int wait_buttons();
			// Wait for a word guess from the player
			string guess_word();
			// Wait for a charactere guess from the player
			char guess_letter();
			// Erase guess box
			void erase_guess();
			// Erase all windows
			void erase_all();
			// Display message from the game
			void display_message(string msg);
			// Erase message box
			void erase_message();

			// GameInterface initializer
			GameInterface(WinData main_box_data);
			GameInterface(WinData main_box_data, int word_max_size);
			// GameInterface destroier
			~GameInterface();

		private:
			// Start game interface based on determined main size
			void initialization(WinData main_box_data);
			
	};
	// Display and behaviour of the initial menu
	int initial_menu(WinData main_box_data);

	// Configuration menu for a new game (display and behaviour)
	void new_game_menu(WinData main_box_data, int *p_n_players, int* p_n_rounds, int* p_n_lifes, vector<string>* names);

	// Interface and behaviour of menu to add a new word to the colection of possible words
	int new_word_menu(WinData main_box_data);

	// Menu to display the rankings
	int ranking_menu(WinData main_box_data);

	// Returns the biggest raking player position in the vector
	int get_first_rank(vector<pair<string, string>> rankings);

	// Display round winner screen
	void round_winner_screen(WinData main_box_data, string name, int points);

	// Display round loser screen when only one player is playing
	void round_loser_screen(WinData main_box_data, string name);

	// Display game winner screen
	int game_winner_screen(WinData main_box_data, string name, int points);
}
#endif