#ifndef PLAYER_H
#define PLAYER_H

#include <string>

namespace hangman
{
  class Player
  {
  public:
    Player(){};
    Player(std::string name_, int lifes, int points)
        : name_(name_), life_(lifes), point_(points){};

    int getLife();
    int getPoint();
    std::string getName();

    void setLife(int life);
    void loseLife(int lost_life);
    void setPoint(int points);
    void setName(std::string name);

    bool getRoundLost();
    void setRoundLost(bool state);
    void loseRound();

    void setID(int id);
    int getID();

  private:
    int id_;
    std::string name_;
    int life_;
    int point_;
    bool round_lost;
  };
}

#endif