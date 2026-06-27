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

int chadin::Squad::getPlayerAt(const int slotIndex) const
{
  if (slotIndex >= 0 && slotIndex < SQUAD_SIZE) {
    return positions_[slotIndex];
  } else {
    return -1;
  }
}

int chadin::Squad::getSlotIndex(const std::string& position) const
{
  if (position == "GK"){
    return 0;
  }
  if (position == "LB"){
    return 1;
  }
  if (position == "CB") {
    if (positions_[2] == -1){
      return 2;
    }
    return 3;
  }
  if (position == "RB"){
    return 4;
  }
  if (position == "CDM"){
    return 5;
  }
  if (position == "CM") {
    if (positions_[6] == -1){
      return 6;
    }
    return 7;
  }
  if (position == "LW"){
    return 8;
  }
  if (position == "RW"){
    return 9;
  }
  if (position == "ST"){
    return 10;
  }
  return -1;
}
