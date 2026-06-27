#include "Squad.hpp"

chadin::Squad::Squad():
  name_(""),
  positions_(SQUAD_SIZE, -1)
{
}

chadin::Squad::Squad(const std::string& name):
  name_(name),
  positions_(SQUAD_SIZE, -1)
{
}

chadin::Squad::~Squad()
{
}

const std::string& chadin::Squad::getName() const
{
  return name_;
}

bool chadin::Squad::addPlayer(const int playerId, const std::string& position)
{
  if (hasPlayer(playerId)) {
    return false;
  }
  int slot = getSlotIndex(position);
  if (slot != -1 && positions_[slot] == -1) {
    positions_[slot] = playerId;
    return true;
  } else {
    return false;
  }
}

bool chadin::Squad::removePlayer(const int playerId)
{
  for (int i = 0; i < SQUAD_SIZE; ++i) {
    if (positions_[i] == playerId) {
      positions_[i] = -1;
      return true;
    }
  }
  return false;
}

void chadin::Squad::clear()
{
  for (int i = 0; i < SQUAD_SIZE; ++i) {
    positions_[i] = -1;
  }
}

bool chadin::Squad::hasPlayer(const int playerId) const
{
  for (int i = 0; i < SQUAD_SIZE; ++i) {
    if (positions_[i] == playerId) {
      return true;
    }
  }
  return false;
}

int chadin::Squad::getPlayerCount() const
{
  int count = 0;
  for (int i = 0; i < SQUAD_SIZE; ++i) {
    if (positions_[i] != -1) {
      count++;
    }
  }
  return count;
}
