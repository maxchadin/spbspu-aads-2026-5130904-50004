#ifndef CHADIN_SQUAD_HPP
#define CHADIN_SQUAD_HPP

#include "Player.hpp"
#include <string>
#include <map>
#include <vector>

namespace chadin {

  class Squad {
  public:
    explicit Squad(const std::string &name);

    std::string getName() const;
    void addPlayer(const Player &player);
    void removePlayer(int id);
    void clear();
    bool hasPlayer(int id) const;

    int getPlayerCount() const;
    std::vector<int> getPlayerIds() const;

    void show() const;

  private:
    std::string name_;
    std::map<std::string, int> positionToPlayerId_;
  };

}

#endif
