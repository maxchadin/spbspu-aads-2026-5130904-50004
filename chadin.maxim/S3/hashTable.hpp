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

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::HashTable(const HashTable& other):
    numBuckets_(other.numBuckets_),
    bucketSize_(other.bucketSize_),
    totalSlots_(other.totalSlots_),
    size_(other.size_),
    table_(new Slot< Key, Value >[other.totalSlots_]),
    hasher_(other.hasher_),
    equals_(other.equals_)
  {
    for (size_t i = 0; i < totalSlots_; ++i) {
      if (other.table_[i].isOccupied_) {
        table_[i].isOccupied_ = true;
        table_[i].key_ = other.table_[i].key_;
        table_[i].value_ = other.table_[i].value_;
      }
    }
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >::~HashTable()
  {
    delete[] table_;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::swap(HashTable& other) noexcept
  {
    std::swap(numBuckets_, other.numBuckets_);
    std::swap(bucketSize_, other.bucketSize_);
    std::swap(totalSlots_, other.totalSlots_);
    std::swap(size_, other.size_);
    std::swap(table_, other.table_);
  }

  template< class Key, class Value, class Hash, class Equal >
  HashTable< Key, Value, Hash, Equal >& HashTable< Key, Value, Hash, Equal >::operator=(HashTable other)
  {
    swap(other);
    return *this;
  }

  template< class Key, class Value, class Hash, class Equal >
  void HashTable< Key, Value, Hash, Equal >::add(const Key& k, const Value& v)
  {
    if (has(k)) {
      get(k) = v;
      return;
    }

    size_t targetBucket = hasher_(k) % numBuckets_;
    size_t startIdx = targetBucket * bucketSize_;

    for (size_t i = 0; i < bucketSize_; ++i) {
      if (!table_[startIdx + i].isOccupied_) {
        table_[startIdx + i].isOccupied_ = true;
        table_[startIdx + i].key_ = k;
        table_[startIdx + i].value_ = v;
        size_++;
        return;
      }
    }

    size_t spareStartIdx = numBuckets_ * bucketSize_;
    for (size_t i = 0; i < bucketSize_; ++i) {
      if (!table_[spareStartIdx + i].isOccupied_) {
        table_[spareStartIdx + i].isOccupied_ = true;
        table_[spareStartIdx + i].key_ = k;
        table_[spareStartIdx + i].value_ = v;
        size_++;
        return;
      }
    }

    throw std::overflow_error("HashTable overflow: buckets and spare bucket are full.");
  }

  template< class Key, class Value, class Hash, class Equal >
  Value HashTable< Key, Value, Hash, Equal >::drop(const Key& k)
  {
    size_t targetBucket = hasher_(k) % numBuckets_;
    size_t startIdx = targetBucket * bucketSize_;

    for (size_t i = 0; i < bucketSize_; ++i) {
      if (table_[startIdx + i].isOccupied_ && equals_(table_[startIdx + i].key_, k)) {
        table_[startIdx + i].isOccupied_ = false;
        size_--;
        return table_[startIdx + i].value_;
      }
    }

    size_t spareStartIdx = numBuckets_ * bucketSize_;
    for (size_t i = 0; i < bucketSize_; ++i) {
      if (table_[spareStartIdx + i].isOccupied_ && equals_(table_[spareStartIdx + i].key_, k)) {
        table_[spareStartIdx + i].isOccupied_ = false;
        size_--;
        return table_[spareStartIdx + i].value_;
      }
    }

    throw std::invalid_argument("Key not found");
  }

  template< class Key, class Value, class Hash, class Equal >
  bool HashTable< Key, Value, Hash, Equal >::has(const Key& k) const
  {
    size_t targetBucket = hasher_(k) % numBuckets_;
    size_t startIdx = targetBucket * bucketSize_;

    for (size_t i = 0; i < bucketSize_; ++i) {
      if (table_[startIdx + i].isOccupied_ && equals_(table_[startIdx + i].key_, k)) {
        return true;
      }
    }

    size_t spareStartIdx = numBuckets_ * bucketSize_;
    for (size_t i = 0; i < bucketSize_; ++i) {
      if (table_[spareStartIdx + i].isOccupied_ && equals_(table_[spareStartIdx + i].key_, k)) {
        return true;
      }
    }
    return false;
  }
