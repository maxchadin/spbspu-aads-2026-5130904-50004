#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "Player.hpp"
#include <vector>
#include <string>

namespace chadin {

class Collection {
public:
  enum class Status {
    EMPTY,
    OCCUPIED,
    DELETED
  };

  struct Entry_t {
    Player player_;
    Status status_;
    int probeDistance_;
  };

  Collection();
  ~Collection();

  bool addPlayer(const Player& player);
  bool removePlayer(int id);
  bool findPlayer(int id, Player& outPlayer) const;
  bool hasPlayer(int id) const;

  const std::vector< Entry_t >& getTable() const;
  int getSize() const;
  int getCapacity() const;
  double getLoadFactor() const;
  int getCollisions() const;
  double getAverageProbe() const;
  int getMaxProbe() const;
  int getRehashCount() const;

  void clear();

private:
  std::vector< Entry_t > table_;
  int size_;
  int capacity_;
  int collisionsTotal_;
  int rehashCount_;
  int maxProbeDist_;
  int totalProbeDist_;

  void rehash();
  int hash(int id) const;
};

}

#endif
