#include "Squad.hpp"
#include <iostream>

namespace chadin {

  Squad::Squad(const std::string &name):
    name_(name)
  {
  }

  std::string Squad::getName() const
  {
    return name_;
  }

  void Squad::addPlayer(const Player &player)
  {
    if (positionToPlayerId_.size() >= 11) {
      throw std::runtime_error("Squad is full (11/11).");
    }
    if (positionToPlayerId_.find(player.getPosition()) != positionToPlayerId_.end()) {
      throw std::runtime_error("Position " + player.getPosition() + " already occupied.");
    }
    if (hasPlayer(player.getId())) {
      throw std::runtime_error("Player already in squad.");
    }

    positionToPlayerId_[player.getPosition()] = player.getId();
  }

  void Squad::removePlayer(int id)
  {
    for (auto it = positionToPlayerId_.begin(); it != positionToPlayerId_.end(); ++it) {
      if (it->second == id) {
        positionToPlayerId_.erase(it);
        return;
      }
    }
    throw std::runtime_error("Player not found in squad.");
  }

  void Squad::clear()
  {
    positionToPlayerId_.clear();
  }

  bool Squad::hasPlayer(int id) const
  {
    for (const auto &pair : positionToPlayerId_) {
      if (pair.second == id) {
        return true;
      }
    }
    return false;
  }

  int Squad::getPlayerCount() const
  {
    return static_cast<int>(positionToPlayerId_.size());
  }

  std::vector<int> Squad::getPlayerIds() const
  {
    std::vector<int> ids;
    for (const auto &pair : positionToPlayerId_) {
      ids.push_back(pair.second);
    }
    return ids;
  }

  void Squad::show() const
  {
    std::cout << "========== SQUAD: \"" << name_ << "\" ==========\n"
              << "Players: " << getPlayerCount() << "/11\n";
    for (const auto &pair : positionToPlayerId_) {
      std::cout << pair.first << " | ID: " << pair.second << "\n";
    }
  }

}
