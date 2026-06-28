#ifndef CHADIN_COLLECTION_HPP
#define CHADIN_COLLECTION_HPP

#include "Player.hpp"
#include <vector>

namespace chadin {

  class Collection {
  public:
    struct HashEntry {
      int id = 0;
      Player player;
      int probeDistance = 0;
      bool isOccupied = false;
      bool isDeleted = false;
    };

    Collection();

    void addPlayer(const Player &player);
    void removePlayer(int id);
    const Player* findPlayer(int id) const;
    void listPlayers() const;
    void showTableStats() const;

    const std::vector<HashEntry>& getTable() const;

  private:
    void rehash();
    void insertHelper(HashEntry entry);

    std::vector<HashEntry> table_;
    int size_;
    int capacity_;
    int collisionsTotal_;
    int rehashCount_;
    int maxProbeDistance_;
  };

}

#endif
