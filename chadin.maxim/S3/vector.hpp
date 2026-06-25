#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <utility>

namespace chadin {
  template< class T >
  class Vector {
  public:
    Vector();
    Vector(const Vector< T >& other);
    ~Vector();

    Vector< T >& operator=(Vector< T > other);
    void swap(Vector< T >& other) noexcept;
    void pushBack(const T& value);
    void erase(size_t index);
    size_t size() const;
    void clear();

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

  private:
    size_t size_;
    size_t capacity_;
    T* data_;
  };

  template< class T >
  Vector< T >::Vector():
    size_(0),
    capacity_(4),
    data_(new T[4])
  {}

  template< class T >
  Vector< T >::Vector(const Vector< T >& other):
    size_(other.size_),
    capacity_(other.capacity_),
    data_(new T[other.capacity_])
  {
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = other.data_[i];
    }
  }

  template< class T >
  Vector< T >::~Vector()
  {
    delete[] data_;
  }

  template< class T >
  void Vector< T >::swap(Vector< T >& other) noexcept
  {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  }

  template< class T >
  Vector< T >& Vector< T >::operator=(Vector< T > other)
  {
    swap(other);
    return *this;
  }

  template< class T >
  void Vector< T >::pushBack(const T& value)
  {
    if (size_ == capacity_) {
      capacity_ *= 2;
      T* newData = new T[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        newData[i] = data_[i];
      }
      delete[] data_;
      data_ = newData;
    }
    data_[size_] = value;
    size_ = size_ + 1;
  }
