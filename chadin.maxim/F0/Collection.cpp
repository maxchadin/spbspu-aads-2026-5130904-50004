#include "Collection.hpp"
#include <algorithm>

const int INITIAL_CAPACITY = 16;

chadin::Collection::Collection():
  table_(INITIAL_CAPACITY),
  size_(0),
  capacity_(INITIAL_CAPACITY),
  collisionsTotal_(0),
  rehashCount_(0),
  maxProbeDist_(0),
  totalProbeDist_(0)
{
  for (int i = 0; i < capacity_; ++i) {
    table_[i].status_ = Status::EMPTY;
    table_[i].probeDistance_ = 0;
  }
}

chadin::Collection::~Collection()
{
}

bool chadin::Collection::addPlayer(const Player& player)
{
  if (hasPlayer(player.getId())) {
    return false;
  }
  const double maxLoadFactor = 0.5;
  if (static_cast< double >(size_) >= maxLoadFactor * capacity_) {
    rehash();
  }
  Entry_t curr{player, Status::OCCUPIED, 0};
  int index = hash(player.getId());
  while (table_[index].status_ == Status::OCCUPIED) {
    if (curr.probeDistance_ > table_[index].probeDistance_) {
      std::swap(curr, table_[index]);
    }
    index = (index + 1) % capacity_;
    curr.probeDistance_++;
    collisionsTotal_++;
  }
  table_[index] = curr;
  size_++;
  totalProbeDist_ += curr.probeDistance_;
  if (curr.probeDistance_ > maxProbeDist_) {
    maxProbeDist_ = curr.probeDistance_;
  }
  return true;
}

bool chadin::Collection::removePlayer(const int id)
{
  int index = hash(id);
  int dist = 0;
  while (table_[index].status_ != Status::EMPTY && dist <= capacity_) {
    if (table_[index].status_ == Status::OCCUPIED && table_[index].player_.getId() == id) {
      table_[index].status_ = Status::DELETED;
      size_--;
      return true;
    }
    index = (index + 1) % capacity_;
    dist++;
  }
  return false;
}

bool chadin::Collection::findPlayer(const int id, Player& outPlayer) const
{
  int index = hash(id);
  int dist = 0;
  while (table_[index].status_ != Status::EMPTY && dist <= capacity_) {
    if (table_[index].status_ == Status::OCCUPIED && table_[index].player_.getId() == id) {
      outPlayer = table_[index].player_;
      return true;
    }
    index = (index + 1) % capacity_;
    dist++;
  }
  return false;
}

bool chadin::Collection::hasPlayer(const int id) const
{
  Player dummy;
  return findPlayer(id, dummy);
}

const std::vector< chadin::Collection::Entry_t >& chadin::Collection::getTable() const
{
  return table_;
}

int chadin::Collection::getSize() const
{
  return size_;
}

int chadin::Collection::getCapacity() const
{
  return capacity_;
}

double chadin::Collection::getLoadFactor() const
{
  if (capacity_ == 0) {
    return 0.0;
  } else {
    return static_cast< double >(size_) / capacity_;
  }
}

int chadin::Collection::getCollisions() const
{
  return collisionsTotal_;
}

double chadin::Collection::getAverageProbe() const
{
  if (size_ == 0) {
    return 0.0;
  } else {
    return static_cast< double >(totalProbeDist_) / size_;
  }
}

int chadin::Collection::getMaxProbe() const
{
  return maxProbeDist_;
}

int chadin::Collection::getRehashCount() const
{
  return rehashCount_;
}
