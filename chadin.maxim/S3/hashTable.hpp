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
