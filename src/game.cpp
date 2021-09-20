#include "game.hpp"

void hangman::Game::Round()
{
  int n_players_left = this->players_amount_;

  // Amount of characters from guess_word right
  // from the last guess
  int n_right_guess = 0;

  // Amount of characters from guessed
  // from the guess_word
  int total_right_guess = 0;

  std::string guess_letter;

  // DEBUG
  this->guess_word_ = "hangman";

  std::string render_guess_word(this->guess_word_.length(), '_');
  this->render_guess_word = render_guess_word;

  // Receive user commands, render, and compute
  while (total_right_guess < this->guess_word_.length())
  // while (n_players_left > 2)
  {
    std::cin >> guess_letter;
    //
    // GuessWord();

    n_right_guess = GuessLetter(guess_letter);
    std::cout << this->render_guess_word << std::endl;
    total_right_guess += n_right_guess;
  }
}

int hangman::Game::GuessLetter(std::string letter)
{
  auto found = this->guess_word_.find(letter);
  int counter = 0;

  // Found
  if (found != std::string::npos)
  {
    // For each letter found, substitutes underscore
    // from the render_string by the letter
    while (found != std::string::npos)
    {
      // If the letter was already guessed, return as
      // no letter guessed
      if (this->render_guess_word[found] != '_')
      {
        return 0;
      }

      counter++;
      this->render_guess_word.replace(found, 1, letter);
      std::cout << "Found at: " << found << " " << this->guess_word_[found] << '\n';
      found = this->guess_word_.find(letter, found + 1);
    }
  }

  // Not found
  else
  {
    std::cout << "Not found" << '\n';
  }

  return counter;
}