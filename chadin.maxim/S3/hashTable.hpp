#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <iterator>

namespace chadin {
  template< class Key, class Value >
  struct Slot {
    bool isOccupied_ = false;
    Key key_;
    Value value_;
  };

  template< class Key, class Value, class Hash, class Equal >
  class HashTable {
  public:
    class Iterator {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = Value;
      using difference_type = std::ptrdiff_t;
      using pointer = Value*;
      using reference = Value&;

      Iterator(Slot< Key, Value >* table, size_t totalSlots, size_t index);
      Iterator& operator++();
      Iterator operator++(int);
      bool operator==(const Iterator& other) const;
      bool operator!=(const Iterator& other) const;
      reference operator*();
      pointer operator->();
      const Key& getKey() const;

    private:
      Slot< Key, Value >* table_;
      size_t totalSlots_;
      size_t index_;

      void advanceToOccupied();
    };

    HashTable(size_t numBuckets = 16, size_t bucketSize = 4);
    HashTable(const HashTable& other);
    ~HashTable();

    HashTable& operator=(HashTable other);
    void swap(HashTable& other) noexcept;

    void add(const Key& k, const Value& v);
    Value drop(const Key& k);
    bool has(const Key& k) const;
    Value& get(const Key& k);
    const Value& get(const Key& k) const;
    void rehash(size_t slots);

    Iterator begin();
    Iterator end();

  private:
    size_t numBuckets_;
    size_t bucketSize_;
    size_t totalSlots_;
    size_t size_;
    Slot< Key, Value >* table_;
    Hash hasher_;
    Equal equals_;
  };

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::Iterator::Iterator(Slot< Key, Value >* table, size_t totalSlots, size_t index):
    table_(table),
    totalSlots_(totalSlots),
    index_(index)
  {
    advanceToOccupied();
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::Iterator::advanceToOccupied()
  {
    while (index_ < totalSlots_ && !table_[index_].isOccupied_) {
      index_++;
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  typename HashTable< Key, Value, Hash, Equal >::Iterator& HashTable< Key, Value, Hash, Equal >::Iterator::operator++()
  {
    index_++;
    advanceToOccupied();
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  typename HashTable< Key, Value, Hash, Equal >::Iterator HashTable< Key, Value, Hash, Equal >::Iterator::operator++(int)
  {
    Iterator temp = *this;
    ++(*this);
    return temp;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::Iterator::operator==(const Iterator& other) const
  {
    return index_ == other.index_ && table_ == other.table_;
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::Iterator::operator!=(const Iterator& other) const
  {
    return !(*this == other);
  }

  template< class Key, class Value, class Hash, class Equal >
  Value& HashTable< Key, Value, Hash, Equal >::Iterator::operator*()
  {
    return table_[index_].value_;
  }

  template< class Key, class Value, class Hash, class Equal >
  Value* HashTable< Key, Value, Hash, Equal >::Iterator::operator->()
  {
    return &(table_[index_].value_);
  }

  template< class Key, class Value, class Hash, class Equal >
  const Key& HashTable< Key, Value, Hash, Equal >::Iterator::getKey() const
  {
    return table_[index_].key_;
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(size_t numBuckets, size_t bucketSize):
    numBuckets_(numBuckets),
    bucketSize_(bucketSize),
    totalSlots_((numBuckets + 1) * bucketSize),
    size_(0),
    table_(new Slot< Key, Value >[totalSlots_])
  {}
