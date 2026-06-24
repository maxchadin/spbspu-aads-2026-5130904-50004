#ifndef CHADIN_BILIST_HPP
#define CHADIN_BILIST_HPP

#include <stdexcept>
#include <utility>
#include <cstddef>
#include "Node.hpp"
#include "LIter.hpp"
#include "LCIter.hpp"

namespace chadin
{
  template< class T >
  class BiList
  {
  public:
    BiList() noexcept : head_(nullptr), size_(0) {}

    BiList(const BiList& other) : head_(nullptr), size_(0)
    {
      if (!other.isEmpty())
      {
        Node< T >* curr = other.head_;
        do
        {
          pushBack(curr->val);
          curr = curr->next;
        }
        while (curr != other.head_);
      }
    }

    BiList(BiList&& other) noexcept : head_(other.head_), size_(other.size_)
    {
      other.head_ = nullptr;
      other.size_ = 0;
    }

    ~BiList() noexcept
    {
      clear();
    }

    BiList& operator=(const BiList& other)
    {
      if (this != &other)
      {
        BiList tmp(other);
        swap(tmp);
      }
      return *this;
    }

    BiList& operator=(BiList&& other) noexcept
    {
      if (this != &other)
      {
        clear();
        head_ = other.head_;
        size_ = other.size_;
        other.head_ = nullptr;
        other.size_ = 0;
      }
      return *this;
    }

    void swap(BiList& other) noexcept
    {
      std::swap(head_, other.head_);
      std::swap(size_, other.size_);
    }

    bool isEmpty() const noexcept
    {
      return size_ == 0;
    }

    size_t getSize() const noexcept
    {
      return size_;
    }

    T& front()
    {
      if (isEmpty()) throw std::out_of_range("List is empty");
      return head_->val;
    }

    const T& front() const
    {
      if (isEmpty()) throw std::out_of_range("List is empty");
      return head_->val;
    }

    T& back()
    {
      if (isEmpty()) throw std::out_of_range("List is empty");
      return head_->prev->val;
    }

    const T& back() const
    {
      if (isEmpty()) throw std::out_of_range("List is empty");
      return head_->prev->val;
    }

    LIter< T > begin() noexcept
    {
      return LIter< T >(head_, head_);
    }

    LIter< T > end() noexcept
    {
      return LIter< T >(nullptr, head_);
    }

    LCIter< T > cbegin() const noexcept
    {
      return LCIter< T >(head_, head_);
    }

    LCIter< T > cend() const noexcept
    {
      return LCIter< T >(nullptr, head_);
    }

    void pushFront(const T& value)
    {
      Node< T >* newNode = new Node< T >(value);
      if (isEmpty())
      {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ = newNode;
      }
      else
      {
        Node< T >* tail = head_->prev;
        newNode->next = head_;
        newNode->prev = tail;
        tail->next = newNode;
        head_->prev = newNode;
        head_ = newNode;
      }
      ++size_;
    }

    void pushFront(T&& value)
    {
      Node< T >* newNode = new Node< T >(std::move(value));
      if (isEmpty())
      {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ = newNode;
      }
      else
      {
        Node< T >* tail = head_->prev;
        newNode->next = head_;
        newNode->prev = tail;
        tail->next = newNode;
        head_->prev = newNode;
        head_ = newNode;
      }
      ++size_;
    }

    void pushBack(const T& value)
    {
      pushFront(value);
      head_ = head_->next;
    }

    void pushBack(T&& value)
    {
      pushFront(std::move(value));
      head_ = head_->next;
    }

    void popFront() noexcept
    {
      if (isEmpty())
      {
        return;
      }
      if (size_ == 1)
      {
        delete head_;
        head_ = nullptr;
      }
      else
      {
        Node< T >* oldHead = head_;
        Node< T >* tail = head_->prev;
        head_ = head_->next;
        head_->prev = tail;
        tail->next = head_;
        delete oldHead;
      }
      --size_;
    }

    void clear() noexcept
    {
      while (!isEmpty())
      {
        popFront();
      }
    }

  private:
    Node< T >* head_;
    size_t size_;
  };
}

#endif
