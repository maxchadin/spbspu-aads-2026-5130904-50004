#ifndef CHADIN_PLAYER_HPP
#define CHADIN_PLAYER_HPP

#include <string>

namespace chadin {

  class Player {
  public:
    Player() = default;
    Player(int id, const std::string &name, const std::string &nation,
           const std::string &league, const std::string &position,
           int pace, int shooting, int passing, int dribbling,
           int defending, int physical);

    int getId() const;
    std::string getName() const;
    std::string getNation() const;
    std::string getLeague() const;
    std::string getPosition() const;

    int getPace() const;
    int getShooting() const;
    int getPassing() const;
    int getDribbling() const;
    int getDefending() const;
    int getPhysical() const;

    double getAverageRating() const;

  private:
    int id_ = 0;
    std::string name_;
    std::string nation_;
    std::string league_;
    std::string position_;

    int pace_ = 0;
    int shooting_ = 0;
    int passing_ = 0;
    int dribbling_ = 0;
    int defending_ = 0;
    int physical_ = 0;
  };

}

#endif
