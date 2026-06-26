#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace chadin {

template <class T>
class Vector {
public:
  Vector():
    data_(nullptr),
    size_(0),
    capacity_(0)
  {
  }

  Vector(const Vector& other):
    data_(new T[other.capacity_]),
    size_(other.size_),
    capacity_(other.capacity_)
  {
    std::copy(other.data_, other.data_ + size_, data_);
  }

  Vector(Vector&& other) noexcept :
    data_(other.data_),
    size_(other.size_),
    capacity_(other.capacity_)
  {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }

  ~Vector()
  {
    delete[] data_;
  }

  Vector& operator=(const Vector& other)
  {
    if (this != &other) {
      Vector tmp(other);
      swap(tmp);
    }
    return *this;
  }

  Vector& operator=(Vector&& other) noexcept
  {
    swap(other);
    return *this;
  }

  void pushBack(const T& value)
  {
    if (size_ == capacity_) {
      size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
      reserve(newCapacity);
    }
    data_[size_++] = value;
  }

  const T& operator[](size_t index) const
  {
    return data_[index];
  }

  T& operator[](size_t index)
  {
    return data_[index];
  }

  size_t size() const
  {
    return size_;
  }

  bool empty() const
  {
    return size_ == 0;
  }

  void swap(Vector& other) noexcept
  {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

private:
  void reserve(size_t newCapacity)
  {
    if (newCapacity <= capacity_) {
      return;
    }
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < size_; ++i) {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
  }

  T* data_;
  size_t size_;
  size_t capacity_;
};

}

#endif
