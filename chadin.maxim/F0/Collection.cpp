#include "Collection.hpp"
#include <iostream>
#include <algorithm>

namespace chadin {

  Collection::Collection():
    table_(16),
    size_(0),
    capacity_(16),
    collisionsTotal_(0),
    rehashCount_(0),
    maxProbeDistance_(0)
  {
  }

  void Collection::addPlayer(const Player &player)
  {
    if (findPlayer(player.getId()) != nullptr) {
      throw std::runtime_error("Player with this ID already exists.");
    }

    if (static_cast<double>(size_) / capacity_ >= 0.5) {
      rehash();
    }

    HashEntry newEntry;
    newEntry.id = player.getId();
    newEntry.player = player;
    newEntry.probeDistance = 0;
    newEntry.isOccupied = true;
    newEntry.isDeleted = false;

    insertHelper(newEntry);
  }

  void Collection::insertHelper(HashEntry entry)
  {
    int currentPos = entry.id % capacity_;

    while (true) {
      if (!table_[currentPos].isOccupied || table_[currentPos].isDeleted) {
        table_[currentPos] = entry;
        size_++;
        if (entry.probeDistance > maxProbeDistance_) {
          maxProbeDistance_ = entry.probeDistance;
        }
        return;
      }

      if (entry.probeDistance > table_[currentPos].probeDistance) {
        std::swap(entry, table_[currentPos]);
      }

      entry.probeDistance++;
      currentPos = (currentPos + 1) % capacity_;
      collisionsTotal_++;
    }
  }

  void Collection::rehash()
  {
    rehashCount_++;
    int oldCapacity = capacity_;
    capacity_ *= 2;
    std::vector<HashEntry> oldTable = table_;

    table_.clear();
    table_.resize(capacity_);
    size_ = 0;

    for (int i = 0; i < oldCapacity; ++i) {
      if (oldTable[i].isOccupied && !oldTable[i].isDeleted) {
        oldTable[i].probeDistance = 0;
        insertHelper(oldTable[i]);
      }
    }
  }

  void Collection::removePlayer(int id)
  {
    int currentPos = id % capacity_;
    int distance = 0;

    while (table_[currentPos].isOccupied) {
      if (!table_[currentPos].isDeleted && table_[currentPos].id == id) {
        table_[currentPos].isDeleted = true;
        size_--;
        return;
      }
      if (distance > table_[currentPos].probeDistance) {
        break;
      }
      distance++;
      currentPos = (currentPos + 1) % capacity_;
    }
    throw std::runtime_error("Player not found.");
  }

  const Player* Collection::findPlayer(int id) const
  {
    if (capacity_ == 0) {
      return nullptr;
    }

    int currentPos = id % capacity_;
    int distance = 0;

    while (table_[currentPos].isOccupied) {
      if (!table_[currentPos].isDeleted && table_[currentPos].id == id) {
        return &table_[currentPos].player;
      }
      if (distance > table_[currentPos].probeDistance) {
        return nullptr;
      }
      distance++;
      currentPos = (currentPos + 1) % capacity_;
    }
    return nullptr;
  }

  void Collection::listPlayers() const
  {
    std::vector<Player> sortedPlayers;
    for (const auto &entry : table_) {
      if (entry.isOccupied && !entry.isDeleted) {
        sortedPlayers.push_back(entry.player);
      }
    }

    std::sort(sortedPlayers.begin(), sortedPlayers.end(),
      [](const Player &a, const Player &b) -> bool {
        return a.getId() < b.getId();
      }
    );

    std::cout << "========== CLUB COLLECTION (Robin Hood Hash Table) ==========\n";
    for (const auto &p : sortedPlayers) {
      std::cout << p.getId() << " | " << p.getName() << " | " << p.getNation() << " | "
                << p.getLeague() << " | " << p.getPosition() << " | " << p.getAverageRating() << "\n";
    }
  }

  void Collection::showTableStats() const
  {
    double loadFactor = capacity_ > 0 ? static_cast<double>(size_) / capacity_ : 0.0;
    double avgProbe = size_ > 0 ? static_cast<double>(collisionsTotal_) / size_ : 0.0;

    std::cout << "========== Robin Hood Hash Table Statistics ==========\n"
              << "Table size: " << capacity_ << "\n"
              << "Elements: " << size_ << "\n"
              << "Load factor: " << loadFactor << "\n"
              << "Collisions total: " << collisionsTotal_ << "\n"
              << "Average probe dist: " << avgProbe << "\n"
              << "Max probe dist: " << maxProbeDistance_ << "\n"
              << "Rehash count: " << rehashCount_ << "\n"
              << "======================================================\n";
  }

  const std::vector<Collection::HashEntry>& Collection::getTable() const
  {
    return table_;
  }

}
