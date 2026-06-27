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
