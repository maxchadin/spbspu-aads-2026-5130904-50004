#include "Player.hpp"

namespace chadin {

  Player::Player(int id, const std::string &name, const std::string &nation,
                 const std::string &league, const std::string &position,
                 int pace, int shooting, int passing, int dribbling,
                 int defending, int physical):
    id_(id),
    name_(name),
    nation_(nation),
    league_(league),
    position_(position),
    pace_(pace),
    shooting_(shooting),
    passing_(passing),
    dribbling_(dribbling),
    defending_(defending),
    physical_(physical)
  {
  }

  int Player::getId() const
  {
    return id_;
  }

  std::string Player::getName() const
  {
    return name_;
  }

  std::string Player::getNation() const
  {
    return nation_;
  }

  std::string Player::getLeague() const
  {
    return league_;
  }

  std::string Player::getPosition() const
  {
    return position_;
  }

  int Player::getPace() const
  {
    return pace_;
  }

  int Player::getShooting() const
  {
    return shooting_;
  }

  int Player::getPassing() const
  {
    return passing_;
  }

  int Player::getDribbling() const
  {
    return dribbling_;
  }

  int Player::getDefending() const
  {
    return defending_;
  }

  int Player::getPhysical() const
  {
    return physical_;
  }

  double Player::getAverageRating() const
  {
    return (pace_ + shooting_ + passing_ + dribbling_ + defending_ + physical_) / 6.0;
  }

}
