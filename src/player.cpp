#include "../include/player.hpp"

void hangman::Player::setLife(int life)
{
  this->life_ = life;
}

void hangman::Player::setPoint(int points)
{
  this->point_ = points;
}

void hangman::Player::setName(std::string name)
{
  this->name_ = name;
}

void hangman::Player::setID(int id)
{
  this->id_ = id;
}

int hangman::Player::getLife()
{
  return this->life_;
}

int hangman::Player::getPoint()
{
  return this->point_;
}

std::string hangman::Player::getName()
{
  return this->name_;
}

int hangman::Player::getID()
{
  return this->id_;
}

void hangman::Player::loseLife(int lost_life)
{
  this->life_ -= lost_life;
}

bool hangman::Player::getRoundLost()
{
  return this->round_lost;
}

void hangman::Player::setRoundLost(bool state)
{
  this->round_lost = state;
}

void hangman::Player::loseRound()
{
  this->round_lost = true;
}