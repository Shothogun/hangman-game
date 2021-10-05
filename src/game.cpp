#include "game.hpp"

int hangman::Game::Round()
{
  // Amount of characters from guess right
  // from the last guess. If not found, it's -1.
  int n_right_guess = 0;

  // Amount of characters from the guess.
  int total_right_guess = 0;

  // Letter guess
  std::string guess;

  // Command choice by user. Assumes L or W
  char choice;

  // Guess word points. If 0, right guess,
  // else is -2 life
  int word_guess_points = -1;

  // Initialize with the 1sr player
  this->player_turn_ = 0;

  // DEBUG
  this->guess_word_ = "hangman";

  bool lost = false;

  const int WRONG = -1;

  this->n_players_left_ = this->players_amount_;

  std::string render_guess_word(this->guess_word_.length(), '_');
  this->render_guess_word = render_guess_word;

  // Receive user commands, render, and compute
  while (this->n_players_left_ >= 2 && word_guess_points != 0)
  {
    std::cout << this->getPlayerName() << "\n";
    std::cout << "Life: " << this->getPlayerLife() << "\n";

    std::cout
        << this->getPlayerName()
        << " have your play choice! (W or L)\n";

    // Choice Reading
    std::cin >> choice;

    // Guess a letter
    if (choice == 'L' || choice == 'l')
    {
      std::cout << this->getPlayerName()
                << ", guess a letter!\n";

      std::cin >> guess;

      n_right_guess = GuessLetter(guess);

      std::cout << "\n\n";
      std::cout << this->render_guess_word << std::endl;

      if (n_right_guess == WRONG)
      {
        lost = false;
        lost = this->loseLife(1);

        if (lost)
        {
          std::cout << "Oh, " << this->getPlayerName()
                    << " lost! :(\n";
        }
      }
    }

    // Guess a word
    else if (choice == 'W' || choice == 'w')
    {
      std::cout << this->getPlayerName()
                << ", guess a word!\n";

      std::cin >> guess;

      word_guess_points = GuessWord(guess);

      if (word_guess_points)
      {
        lost = this->loseLife(word_guess_points);
      }

      else
      {
        break;
      }
    }

    else
    {
      std::cout << "Invalid choice. "
                << this->getPlayerName()
                << ". Choose 'W' or 'L',";

      continue;
    }

    UpdatePlayerTurn();

    std::cout << "\n\n\n";
  }

  std::cout << this->getPlayerName() << ", U are the WINNER!!! :D\n";
  return this->getPlayerID();
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
        std::cout << "Already guessed letter! Skip turn.\n";
        return 0;
      }

      counter++;
      this->render_guess_word.replace(found, 1, letter);
      found = this->guess_word_.find(letter, found + 1);
    }
  }

  // Not found
  else
  {
    counter = -1;
  }

  return counter;
}

int hangman::Game::GuessWord(std::string word)
{
  if (!this->guess_word_.compare(word))
  {
    std::cout << "Right guess! :)\n";
    return 0;
  }

  else
  {
    std::cout << "Wrong guess! :(\n";
    return 3;
  }
}

void hangman::Game::RoundPlayersInit()
{
  for (size_t i = 0; i < this->players_amount_; i++)
  {
    hangman::Player *p = new Player();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 1000000.0);

    this->game_players_.push_back(p);
    this->game_players_[i]->setPoint(0);
    this->game_players_[i]->setRoundLost(false);
    this->game_players_[i]->setID(dist(mt));
  }
}

void hangman::Game::setPlayersName(std::vector<std::string> names)
{
  for (size_t i = 0; i < this->players_amount_; i++)
  {
    this->game_players_[i]->setName(names[i]);
  }
}

void hangman::Game::setPlayersLife(int amount)
{
  this->lifes_ = amount;
  for (size_t i = 0; i < this->players_amount_; i++)
  {
    this->game_players_[i]->setLife(this->lifes_);
  }
}

void hangman::Game::UpdatePlayerTurn()
{
  do
  {
    this->player_turn_++;
    this->player_turn_ %= this->players_amount_;
  } while (this->game_players_[this->player_turn_]->getRoundLost());
}

std::string hangman::Game::getPlayerName()
{
  return this->game_players_[this->player_turn_]->getName();
}

int hangman::Game::getPlayerLife()
{
  return this->game_players_[this->player_turn_]->getLife();
}

int hangman::Game::getPlayerID()
{
  return this->game_players_[this->player_turn_]->getID();
}

void hangman::Game::setPlayerAmount(int amount)
{
  this->players_amount_ = amount;
}

bool hangman::Game::loseLife(int lost_life)
{
  this->game_players_[this->player_turn_]->loseLife(lost_life);
  if (!this->game_players_[this->player_turn_]->getLife())
  {
    this->n_players_left_--;
    this->game_players_[this->player_turn_]->loseRound();
    return true;
  }

  return false;
}