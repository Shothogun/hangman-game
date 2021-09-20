#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"

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

    void Round();

    int GuessLetter(std::string letter);

  private:
    std::string guess_word_{""};
    std::string render_guess_word;

    // Size to render on screen the
    // word
    int guess_word_size_;
    // How many lives each player have
    int lifes_{3};
    // How many player per turn
    int players_amount_{4};
    // Winner player id's on the game
    int winner_;
    // Amount of rounds per game
    int rounds_{3};

    std::vector<hangman::Player> game_players_;

    std::vector<int> players_points_;
  };
}

#endif