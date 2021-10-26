#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"
#include "interfaces.hpp"
#include <random>

namespace hangman
{
  class Game
  {
  public:
    Game(){};

    Game(std::string guess_word, int lifes, int players_amount,
         int rounds)
        : guess_word_(guess_word), lifes_(lifes), rounds_(rounds),
          players_amount_(players_amount){};

    int Round(GameInterface *game_interface);

    int GuessLetter(std::string letter);

    int GuessWord(std::string word);
    void setPlayerAmount(int amount);

    void RoundPlayersInit();
    void RoundPlayersSoftReset(int number_lifes);
    void setPlayersName(std::vector<std::string> names);
    void setPlayersLife(int amount);

    // Adds 1 at players index. If reachs the utmost,
    // resets to 0.
    void UpdatePlayerTurn();

    // Gets current player name
    std::string getPlayerName();

    // Gets current player life amount
    int getPlayerLife();

    int getPlayerID();

    int getPlayersAmount();

    std::vector<hangman::Player *> getGamePlayers();

    // Makes current player lose life
    // Return if lost the turn.
    bool loseLife(int lost_life);

  private:
    std::string guess_word_{""};
    std::string render_guess_word;

    // Size to render on screen the
    // word
    int guess_word_size_;
    // How many lives each player have
    int lifes_{4};
    // How many player per turn
    int players_amount_{4};
    // Winner player id's on the game
    int winner_;
    // Amount of rounds per game
    int rounds_{3};

    // Player turn's id
    int player_turn_;

    // Amount of players left on the game
    int n_players_left_;

    // Amount of life lost when a letter is wrong
    // guessed. 
    int letter_life_lose;

    // Amount of life lost when a word is wrong
    // guessed. Represents 50% of the total original life.
    int word_life_lose;

    std::vector<hangman::Player *>
        game_players_;
  };
}

#endif