#include "../include/game.hpp"
#include "../include/file.hpp"

int hangman::Game::Round(GameInterface *game_interface)
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

  // Guess word points
  int word_guess_points = -1;

  // Initialize with the 1sr player
  this->player_turn_ = 0;

  // Take a random word from the file with all posibly words
  this->guess_word_ = randomWord(allWords("src/words.txt"));

  bool lost = false;

  const int WRONG = -1;

  this->n_players_left_ = this->players_amount_;

  std::string render_guess_word(this->guess_word_.length(), '_');
  this->render_guess_word = render_guess_word;

  int end_condition = 0;

  // Receive user commands, render, and compute
  // If there's still players left and no one guessed the word
  while (1)
  {
    game_interface->display_player(this->getPlayerName(), this->getPlayerLife(), this->getPlayerPoint());

    game_interface->display_cur_word(this->render_guess_word);

    game_interface->display_buttons();

    // Choice Reading
    choice = game_interface->wait_buttons();
    game_interface->erase_buttons();
    //std::cin >> choice;

    // Guess a letter
    if (choice == 1)
    {
      guess = std::string(1, game_interface->guess_letter());
      //mvwprintw(stdscr, 0, 0, guess.c_str());

      n_right_guess = GuessLetter(guess);

      game_interface->display_cur_word(this->render_guess_word);

      if (n_right_guess == WRONG)
      {
        this->game_players_[this->player_turn_]->setPoint(this->game_players_[this->player_turn_]->getPoint() - 1);
        lost = false;
        lost = this->loseLife(letter_life_lose);

        if (lost)
        {
          game_interface->display_message("Oh, " + this->getPlayerName() + " perdeu!");
        }
        else
          game_interface->display_message("Ops, não tem essa letra!");
      }
      else if (n_right_guess == 0)
        game_interface->display_message("Letra já utilizada!");

      else{
        this->game_players_[this->player_turn_]->setPoint(this->game_players_[this->player_turn_]->getPoint() + 1);
        if(GuessWord(this->render_guess_word))
        {
          game_interface->display_message("Muito bom!");
        }
        else{
          game_interface->display_message("Palavra correta!"); 
          break;
        }
      }
    }

    // Guess a word
    else if (choice == 2) //(choice == 'W' || choice == 'w')
    {
      guess = game_interface->guess_word();

      word_guess_points = GuessWord(guess);

      game_interface->display_cur_word(this->render_guess_word);

      if (word_guess_points)
      {
        this->game_players_[this->player_turn_]->setPoint(this->game_players_[this->player_turn_]->getPoint() - 3);
        lost = this->loseLife(word_life_lose);

        if (lost)
        {
          game_interface->display_message("Palavra errada! " + this->getPlayerName() + " perdeu!");
        }
        else
        {
          game_interface->display_message("Palavra errada! -" +
                                          std::to_string(word_life_lose) + " vidas!");
        }
      }

      else
      {
        this->game_players_[this->player_turn_]->setPoint(this->game_players_[this->player_turn_]->getPoint() + 3);
        game_interface->display_message("Palavra correta!");
        break;
      }
    }

    // If the solo player lost, leave; else update player turn
    if (this->n_players_left_ == 0 && players_amount_ == 1)
    {
      break;
    }
    else
      UpdatePlayerTurn();

    // Right word guess
    if (word_guess_points == 0)
    {
      break;
    }

    // If only one survivor player of many, leave
    if (this->n_players_left_ == 1 && players_amount_ > 1)
    {
      break;
    }


    timeout(2000);
    getch();
    game_interface->erase_guess();
    game_interface->erase_message();
    timeout(-1);

    //std::cout << "\n\n\n";
  }

  game_interface->erase_all();

  //std::cout << this->getPlayerName() << ", U are the WINNER!!! :D\n";
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
    this->render_guess_word = word;
    return 0;
  }

  else
  {
    return 1;
  }
}

void hangman::Game::RoundPlayersInit()
{
  this->game_players_.clear();
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

void hangman::Game::RoundPlayersSoftReset(int number_lifes)
{
  for (size_t i = 0; i < this->players_amount_; i++)
  {
    this->setPlayersLife(number_lifes);
    this->game_players_[i]->setRoundLost(false);
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
  this->letter_life_lose = 1;
  this->word_life_lose = this->lifes_ / 2;
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

int hangman::Game::getPlayerPoint()
{
  return this->game_players_[this->player_turn_]->getPoint();
}

int hangman::Game::getPlayersAmount(){
  return this->players_amount_;
}

void hangman::Game::setPlayerAmount(int amount)
{
  this->players_amount_ = amount;
}

bool hangman::Game::loseLife(int lost_life)
{
  this->game_players_[this->player_turn_]->loseLife(lost_life);
  if (this->game_players_[this->player_turn_]->getLife() <= 0)
  {
    this->n_players_left_--;
    this->game_players_[this->player_turn_]->loseRound();
    return true;
  }

  return false;
}

std::vector<hangman::Player *> hangman::Game::getGamePlayers(){
  return this->game_players_;
}