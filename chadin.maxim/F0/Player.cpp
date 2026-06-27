#include "Player.hpp"

chadin::Player::Player():
  id_(0),
  name_(""),
  nation_(""),
  league_(""),
  position_(""),
  pace_(0),
  shooting_(0),
  passing_(0),
  dribbling_(0),
  defending_(0),
  physical_(0)
{
}

chadin::Player::Player(const int id, const std::string& name, const std::string& nation,
                       const std::string& league, const std::string& pos, const int pac,
                       const int sho, const int pas, const int dri, const int def, const int phy):
  id_(id),
  name_(name),
  nation_(nation),
  league_(league),
  position_(pos),
  pace_(pac),
  shooting_(sho),
  passing_(pas),
  dribbling_(dri),
  defending_(def),
  physical_(phy)
{
}

int chadin::Player::getId() const
{
  return id_;
}

const std::string& chadin::Player::getName() const
{
  return name_;
}

const std::string& chadin::Player::getNation() const
{
  return nation_;
}

const std::string& chadin::Player::getLeague() const
{
  return league_;
}

const std::string& chadin::Player::getPosition() const
{
  return position_;
}

int chadin::Player::getPace() const
{
  return pace_;
}

int chadin::Player::getShooting() const
{
  return shooting_;
}

int chadin::Player::getPassing() const
{
  return passing_;
}

int chadin::Player::getDribbling() const
{
  return dribbling_;
}

int chadin::Player::getDefending() const
{
  return defending_;
}

int chadin::Player::getPhysical() const
{
  return physical_;
}

double chadin::Player::getRating() const
{
  const double statsCount = 6.0;
  return (pace_ + shooting_ + passing_ + dribbling_ + defending_ + physical_) / statsCount;
}
