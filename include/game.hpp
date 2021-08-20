#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <iostream>
#include <string>

namespace HANGMAN
{
  class game
  {
  private:
    std::string guess_word_ = "";
    int guess_word_size_;
    int lifes_ = 3;
    int players_amount_ = 4;

  public:
  };
}

#endif