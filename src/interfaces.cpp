#include "../include/interfaces.hpp"

using namespace std;

namespace hangman {

	// Box initializer - set starting coordinates and dimensions and create window
	Box::Box(int starty, int startx, int height, int width) {
		this->startx = startx;
		this->starty = starty;
		this->height = height;
		this->width = width;
		this->win = newwin(height+2, width+2, starty-1, startx-1);
	}

	// Box destructor erase and delete window
	Box::~Box(){
		werase(this->win);
		wrefresh(this->win);
		delwin(this->win);
	}

	// Write text message in the center of the box in the line informed
	void Box::write_center(string str, int line) {
		if (line < this->height){
			if (str.size() > uint(this->width)){
				str.resize(this->width);
			}
			mvwprintw(this->win, line+1, int(this->width/2 - str.size()/2)+1, str.c_str());
		}
		wrefresh(this->win);
	}

	// Write text message in the beginning of the box in the line informed
	void Box::write_begin(string str, int line) {
		if (line < this->height){
			if (str.size() > uint(this->width)){
				str.resize(this->width);
			}
			mvwprintw(this->win, line+1, 1, str.c_str());
		}
		wrefresh(this->win);
	}

	// Wait for a string input from the user in line and position (y, x) of the box
	string Box::read_str(int line, int position) {
		char s[80];

		echo();
		mvwgetstr(this->win, line + 1, position + 1, s);
		noecho();
		string str(s);

		return str;
	}

	// Wait for a character input from the user in line and position (y, x) of the box
	char Box::read_char(int line, int position) {
		char c;

		echo();
		c = mvwgetch(this->win, line + 1, position + 1);
		noecho();

		return c;
	}

	// Create a border arround the box
	void Box::create_border() {
		box(this->win, 0, 0);
		wrefresh(this->win);
	}

	// Return if the general coordenates (x, y) are a part of this box
	int Box::isThisButton(int x, int y) {
		if (x >= this->startx && x <= this->startx + this->width && y >= this->starty && y <= this->starty + this->height){
			return 1;
		}
		else return 0;
	}

	// Start game interface based on determined main size
	void GameInterface::initialization(WinData main_box_data){
		int margin_y = 3, margin_x = 2;
		int hang_space = 5, hang_height = 6;
		int but_height = 15;
		int separation = int(main_box_data.width/2);
		int msg_y = 18;

		// Limits the word size to the width of the main box
		if (this->word_max_size + hang_space*2 > main_box_data.width) this->word_max_size = main_box_data.width - hang_space*2;

		// Create the boxes used
		this->current_player = new Box(margin_y + main_box_data.starty, main_box_data.startx + margin_x, 2, main_box_data.width - 2*margin_x);
		this->cur_word = new Box(main_box_data.starty + int((main_box_data.height - hang_height)/2), main_box_data.startx + int(main_box_data.width- this->word_max_size)/2 - hang_space, 
								 hang_height, this->word_max_size + hang_space*2);
		this->button_letter = new Box(main_box_data.starty + but_height, int(1*separation/3) + main_box_data.startx, 2, int(separation*1/2));
		this->button_word = new Box(main_box_data.starty + but_height, int(7*separation/6) + main_box_data.startx, 2, int(separation*1/2));
		this->guess = new Box(main_box_data.starty + but_height, int(1*separation/3) + main_box_data.startx, 1, main_box_data.width - int(1*separation/3) - 1);
		this->msg = new Box(main_box_data.starty + msg_y, main_box_data.startx + margin_x, 1, main_box_data.width - 2*margin_x);
	}

	// GameInterface initializer - calls initialization method based on main size and word max size
	GameInterface::GameInterface(WinData main_box_data, int word_max_size){
		this->word_max_size = word_max_size;
		this->initialization(main_box_data);
	}

	// GameInterface initializer - calls initialization method based on main size
	GameInterface::GameInterface(WinData main_box_data){
		this->initialization(main_box_data);
	}

	// Erase all windows
	void GameInterface::erase_all(){
		this->current_player->erase();
		this->current_player->refresh();
		this->cur_word->erase();
		this->cur_word->refresh();
		this->erase_buttons();
		this->erase_guess();
		this->erase_message();
	}

	// GameInterface destroyer - delete all windows
	GameInterface::~GameInterface(){
		delete this->current_player;
		delete this->cur_word;
		delete this->button_word;
		delete this->button_letter;
		delete this->guess;
		delete this->msg;
	}

	// Display player name and health
	void GameInterface::display_player(string name, int life){
		this->current_player->erase();
		wattron(this->current_player->win, A_BOLD|A_UNDERLINE);
		this->current_player->write_center(name, 0);
		wattroff(this->current_player->win, A_UNDERLINE);
		this->current_player->write_center("Vidas: " + to_string(life), 1);
	}

	// Display current state of the guessing word
	void GameInterface::display_cur_word(string word){
		this->cur_word->erase();
		this->cur_word->write_begin("____ ", 0);
		this->cur_word->write_begin("|  | ", 1);
		this->cur_word->write_begin("|  O ", 2);
		this->cur_word->write_begin("| /|\\", 3);
		this->cur_word->write_begin("| / \\", 4);
		wattron(this->cur_word->win, A_BOLD);
		this->cur_word->write_center(word, 4);
	}

	// Display message from the game
	void GameInterface::display_message(string msg){
		this->msg->erase();
		wattron(this->msg->win, A_BOLD|A_STANDOUT);
		this->msg->write_center(msg, 0);
	}

	// Wait for a charactere guess from the player 
	char GameInterface::guess_letter(){
		string s = "Escreva a letra escolhida: ";

		this->guess->erase();
		this->guess->write_begin(s, 0);

		return this->guess->read_char(0, s.size());
	}

	// Wait for a word guess from the player
	string GameInterface::guess_word(){
		string s = "Escreva a palavra escolhida: ";

		this->guess->erase();
		this->guess->write_begin(s, 0);

		return this->guess->read_str(0, s.size());
	}

	// Display the two buttons
	void GameInterface::display_buttons(){
		this->button_word->erase();
		this->button_letter->erase();
		button_letter->create_border();
		button_letter->write_center("Adivinhar letra", 0);
		button_letter->write_center("(1)", 1);
		button_word->create_border();
		button_word->write_center("Adivinhar palavra", 0);
		button_word->write_center("(2)", 1);
	}

	// Erase the two buttons
	void GameInterface::erase_buttons(){
		this->button_word->erase();
		this->button_letter->erase();
		this->button_word->refresh();
		this->button_letter->refresh();
	}

	// Erase guess box
	void GameInterface::erase_guess(){
		this->guess->erase();
		this->guess->refresh();
	}

	// Erase message box
	void GameInterface::erase_message(){
		this->msg->erase();
		this->msg->refresh();
	}

	// Wait the selection of a button
	int GameInterface::wait_buttons(){
		int ch = 0, next_page = 0;

		MEVENT event;
		mousemask(ALL_MOUSE_EVENTS, NULL);
		
		while(ch != 27){
			ch = getch();
			switch(ch){
				case '1':
					next_page = 1;
					ch = 27;
					break;
				case '2':
					next_page = 2;
					ch = 27;
					break;
				case KEY_MOUSE:
					if(getmouse(&event) == OK){
						if(event.bstate & BUTTON1_PRESSED || event.bstate & BUTTON1_CLICKED){
							if (this->button_letter->isThisButton(event.x, event.y)){
								next_page = 1;
								ch = 27;
							}
							else if (this->button_word->isThisButton(event.x, event.y)){
								next_page = 2;
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

		//Disable mouse events
		mousemask(0, NULL);

		return next_page;
	}

	// Display and behaviour of the initial menu
	int initial_menu(WinData main_box_data){
		int separation;
		int ch, next_page = 0;
		int n_choices = 3;

		MEVENT event;

		separation = int(main_box_data.width/n_choices) + 1;

		// Create the text
		Box text (5 + main_box_data.starty, main_box_data.startx + 1, 2, main_box_data.width - 2);
		wattron(text.win, A_BOLD|A_UNDERLINE);
		text.write_center("Bem-vindo ao jogo da forca!", 0);

		// Create the buttons
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
		
		// Wait and proceed depending on user action
		while(ch != EXIT){
			ch = getch();
			switch(ch){
				case '1':
					next_page = GAME;
					ch = EXIT;
					break;
				case '2':
					next_page = RANK;
					ch = EXIT;
					break;
				case '3':
					next_page = NWORD;
					ch = EXIT;
					break;
				case KEY_MOUSE:
					if(getmouse(&event) == OK){
						if(event.bstate & BUTTON1_PRESSED || event.bstate & BUTTON1_CLICKED){
							if (b1.isThisButton(event.x, event.y)){
								next_page = GAME;
								ch = EXIT;
							}
							else if (b2.isThisButton(event.x, event.y)){
								next_page = RANK;
								ch = EXIT;
							}
							else if(b3.isThisButton(event.x, event.y)){
								next_page = NWORD;
								ch = EXIT;
							}
							else if (bexit.isThisButton(event.x, event.y)){
								next_page = EXIT;
								ch = EXIT;
							}
						}
					}
					break;
				case EXIT:
					next_page = EXIT;
					break;
				default:
					break;
			}
		}

		// Disable mouse events
		mousemask(0, NULL);

		return next_page;
	}


	// Configuration menu for a new game (display and behaviour)
	void new_game_menu(WinData main_box_data, int *p_n_players, int* p_n_rounds, int* p_n_lifes, vector<string>* names){
		int margin_y = 3, margin_x = 2, separation = 3;
		string str_q1 = "Escreva a quantidade de jogadores: ";
		string str_q2 = "Escreva a quantidade de rodadas: ";
		string str_q3 = "Escreva a quantidade de vidas por jogador: ";
		string str_q4 = "Escreva o nome do jogador ";

		// Create boxes and wait for player to respond
		Box q1 (margin_y + main_box_data.starty, margin_x + main_box_data.startx, 1, main_box_data.width - margin_x*2);
		q1.write_begin(str_q1, 0);
		*p_n_players = stoi(q1.read_str(0, str_q1.size()));
		Box q2 (q1.starty + q1.height + separation, margin_x + main_box_data.startx, 1, main_box_data.width - margin_x*2);
		q2.write_begin(str_q2, 0);
		*p_n_rounds = stoi(q2.read_str(0, str_q2.size()));
		Box q3 (q2.starty + q2.height + separation, margin_x + main_box_data.startx, 1, main_box_data.width - margin_x*2);
		q3.write_begin(str_q3, 0);
		*p_n_lifes = stoi(q3.read_str(0, str_q3.size()));

		Box q4 (q3.starty + q3.height + separation, margin_x + main_box_data.startx, 1, main_box_data.width - margin_x*2);

		for (int i = 0; i < *p_n_players; i++){
			q4.write_begin(str_q4 + to_string(i+1) + " : ", 0);
			names->push_back(q4.read_str(0, (str_q4 + to_string(i+1) + " : ").size()));
			q4.erase();
		}

		Box text (q4.starty + q4.height + separation-1, margin_x + main_box_data.startx, 1, main_box_data.width - margin_x*2);
		wattron(text.win, A_BOLD|A_UNDERLINE|A_STANDOUT);
		text.write_center("Tudo configurado! Clique ou aperte qualquer tecla para começar!", 0);

		// Enable mouse events
		mousemask(ALL_MOUSE_EVENTS, NULL);

		// Wait for response
		getch();

		// Disable mouse events
		mousemask(0, NULL);

	}

	// Interface and behaviour of menu to add a new word to the colection of possible words
	int new_word_menu(WinData main_box_data){

		int ch = 0, next_page = 0;
		int n_choices = 2;
		int margin_x = 2;
		int but_height = int(3*main_box_data.height/4);
		int separation = int(main_box_data.width/n_choices);
		string str = "Escreva a nova palavra: ";
		string new_word;
		std::size_t found;

		MEVENT event;

		// Create the text and wait for response
		Box text (int(main_box_data.height/4) + main_box_data.starty, main_box_data.startx + 1, 2, main_box_data.width - 2);
		wattron(text.win, A_BOLD);
		text.write_begin(str, 0);
		wattroff(text.win, A_BOLD);
		new_word = text.read_str(0, str.size());
		found = new_word.find(' ');
		if (found != string::npos)
			new_word = new_word.substr(0, found);

		//Insert word in the words file
		writeWord(new_word, "src/words.txt");

		// Box with system message
		Box msg (main_box_data.starty + int(main_box_data.height/2), main_box_data.startx + margin_x, 1, main_box_data.width - margin_x*2);
		wattron(msg.win, A_BOLD|A_UNDERLINE|A_STANDOUT);
		msg.write_center("Sucesso! Palavra '" + new_word + "' adicionada!", 0);

		// Create buttons
		Box button_back (main_box_data.starty + but_height, int(1*separation/3) + main_box_data.startx, 2, int(separation*1/2));
		Box button_again (main_box_data.starty + but_height, int(7*separation/6) + main_box_data.startx, 2, int(separation*1/2));
		button_again.create_border();
		button_again.write_center("Adicionar outra", 0);
		button_again.write_center(" palavra (2)", 1);
		button_back.create_border();
		button_back.write_center("Voltar ao menu", 0);
		button_back.write_center("(1)", 1);

		// Allow mouse events
		mousemask(ALL_MOUSE_EVENTS, NULL);

		// Buttons behavior
		while(ch != 27){
			ch = getch();
			switch(ch){
				case '1':
					next_page = MAIN; // Page 0 = main
					ch = EXIT;
					break;
				case '2':
					next_page = NWORD; // Page 3 = add word
					ch = EXIT;
					break;
				case KEY_MOUSE:
					if(getmouse(&event) == OK){
						if(event.bstate & BUTTON1_PRESSED || event.bstate & BUTTON1_CLICKED){
							if (button_back.isThisButton(event.x, event.y)){
								next_page = MAIN;
								ch = EXIT;
							}
							else if (button_again.isThisButton(event.x, event.y)){
								next_page = NWORD;
								ch = EXIT;
							}
						}
					}
					break;
				case EXIT:
					next_page = EXIT;
					break;
				default:
					break;
			}
		}

		// Disable mouse events
		mousemask(0, NULL);

		return next_page;
	}

	int ranking_menu(WinData main_box_data){

		int index, counter = 0, max_rankings;
		int margin_x = 2, margin_y = 3;
		int column, line, n_columns = 3;
		int column_width, column_height, column_y;
		int msg_y = int(7*main_box_data.height/8);
		int separation = int(main_box_data.width/n_columns);
		string tmp_str;
		vector<pair<string, string>> rankings;

		column_height = int(7*main_box_data.height/8) - 2*margin_y + 1;
		column_width = int(3*separation/4);
		column_y = main_box_data.starty + margin_y;

		// Boxes of the three columns to display the rankings
		Box rank_columns [3] = {
			Box(column_y, main_box_data.startx + int(1*separation/6), column_height, column_width),
			Box(column_y, main_box_data.startx + int(9*separation/8), column_height, column_width),
			Box(column_y, main_box_data.startx + int(25*separation/12), column_height, column_width)
		};

		// TODO: Rankings Title

		// Get rankings
		rankings = readRanking("src/ranking.txt");

		// Max rankings displayed
		max_rankings = int(column_height/2) * n_columns;

		line = 0;
		column = 0;
		// Display the best ranked players one at a time
		while(rankings.size() > 0 && counter < max_rankings){
			// Get the best ranked player
			index = get_first_rank(rankings);
			// If changing the column, reset line number
			if (column != int(counter*n_columns/max_rankings)){
				column = int(counter*n_columns/max_rankings);
				line = 0;
			}
			// Display player data
			tmp_str = to_string(counter+1) + ". " + rankings[index].first + " - " + rankings[index].second;
			if (tmp_str.size() > uint(rank_columns[column].width))
			{
				tmp_str = tmp_str.substr(0, uint(rank_columns[column].width));
			}
			rank_columns[column].write_begin(tmp_str, line);
			// Update for the next player
			line += 2;
			counter++;
			// Remove the best ranked player
			rankings.erase(rankings.begin() + index);
		}

		// System message display
		Box text (main_box_data.starty + msg_y, main_box_data.startx + margin_x, 1, main_box_data.width - margin_x*2);
		wattron(text.win, A_BOLD|A_UNDERLINE|A_STANDOUT);
		text.write_center("Clique ou aperte qualquer tecla para voltar!", 0);

		// Enable mouse events
		mousemask(ALL_MOUSE_EVENTS, NULL);

		// Wait for response
		getch();

		// Disable mouse events
		mousemask(0, NULL);

		// Returns to the initial menu
		return MAIN;
	}

	// Returns the biggest raking player position in the vector
	int get_first_rank(vector<pair<string, string>> rankings){
		int max = numeric_limits<int>::min();
		int id = -1;

		// Go through the role vector comparing with the biggest pontuation known
		for (uint i = 0; i < rankings.size(); i++){
			if (stoi(rankings[i].second) > max) {
				max = stoi(rankings[i].second);
				id = i;
			}
		}

		return id;
	}

	int game_winner_screen(WinData main_box_data, string name){
		int ch = 0, next_page = 0;
		int n_choices = 2;
		int margin_x = 2;
		int but_height = int(3*main_box_data.height/4);
		int separation = int(main_box_data.width/n_choices);

		MEVENT event;

		// Create the text
		Box text (int(main_box_data.height/4) + main_box_data.starty, main_box_data.startx + 1, 1, main_box_data.width - 2);
		wattron(text.win, A_BOLD|A_UNDERLINE);
		text.write_center("Parabéns " + name + "! Você ganhou essa rodada!", 0);

		// Box with system message
		Box msg (main_box_data.starty + int(main_box_data.height/2), main_box_data.startx + margin_x, 1, main_box_data.width - margin_x*2);
		wattron(msg.win, A_BOLD|A_UNDERLINE|A_STANDOUT);
		msg.write_center("Sua pontuação será adicionada ao ranking!", 0);

		// Create buttons
		Box button_back (main_box_data.starty + but_height, int(1*separation/3) + main_box_data.startx, 2, int(separation*1/2));
		Box button_again (main_box_data.starty + but_height, int(7*separation/6) + main_box_data.startx, 2, int(separation*1/2));
		button_again.create_border();
		button_again.write_center("Jogar novamente", 0);
		button_again.write_center("(2)", 1);
		button_back.create_border();
		button_back.write_center("Voltar ao menu", 0);
		button_back.write_center("(1)", 1);

		// Allow mouse events
		mousemask(ALL_MOUSE_EVENTS, NULL);

		// Buttons behavior
		while(ch != 27){
			ch = getch();
			switch(ch){
				case '1':
					next_page = MAIN; // Page 0 = main
					ch = EXIT;
					break;
				case '2':
					next_page = GAME; // Page 1 = play a new game
					ch = EXIT;
					break;
				case KEY_MOUSE:
					if(getmouse(&event) == OK){
						if(event.bstate & BUTTON1_PRESSED || event.bstate & BUTTON1_CLICKED){
							if (button_back.isThisButton(event.x, event.y)){
								next_page = MAIN;
								ch = EXIT;
							}
							else if (button_again.isThisButton(event.x, event.y)){
								next_page = GAME;
								ch = EXIT;
							}
						}
					}
					break;
				case EXIT:
					next_page = EXIT;
					break;
				default:
					break;
			}
		}

		// Disable mouse events
		mousemask(0, NULL);

		return next_page;
	}

	void round_winner_screen(WinData main_box_data, string name){

		int margin_x = 2;
		int msg_y = int(7*main_box_data.height/8);

		// Create the winning text
		Box text (int(main_box_data.height/3) + main_box_data.starty, main_box_data.startx + 1, 1, main_box_data.width - 2);
		wattron(text.win, A_BOLD|A_UNDERLINE);
		text.write_center("Parabéns " + name + "! Você ganhou essa rodada!", 0);

		// Box with system message
		Box msg (main_box_data.starty + msg_y, main_box_data.startx + margin_x, 1, main_box_data.width - margin_x*2);
		wattron(msg.win, A_BOLD|A_UNDERLINE|A_STANDOUT);
		msg.write_center("Clique ou aperte qualquer tecla para voltar!", 0);

		// Enable mouse events
		mousemask(ALL_MOUSE_EVENTS, NULL);

		// Wait for response
		getch();

		// Disable mouse events
		mousemask(0, NULL);
	}

}