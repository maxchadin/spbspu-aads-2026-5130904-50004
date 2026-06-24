#ifndef CHADIN_BILIST_HPP
#define CHADIN_BILIST_HPP

#include <stdexcept>
#include <utility>
#include <cstddef>
#include <iterator>

namespace chadin
{
  template< class T >
  struct Node
  {
    T val;
    Node* prev;
    Node* next;
    explicit Node(const T& value) : val(value), prev(nullptr), next(nullptr) {}
    explicit Node(T&& value) : val(std::move(value)), prev(nullptr), next(nullptr) {}
  };

  template< class T >
  class BiList;

  template< class T >
  class LCIter;

  template< class T >
  class LIter
  {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    friend class BiList< T >;
    friend class LCIter< T >;

    LIter() : node_(nullptr), head_(nullptr) {}

    reference operator*() const { return node_->val; }
    pointer operator->() const { return &(node_->val); }

    LIter& operator++()
    {
      if (node_)
      {
        node_ = node_->next;
        if (node_ == head_)
        {
          node_ = nullptr;
        }
      }
      return *this;
    }

    LIter operator++(int)
    {
      LIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LIter& operator--()
    {
      if (!node_)
      {
        if (head_)
        {
          node_ = head_->prev;
        }
      }
      else if (node_ != head_)
      {
        node_ = node_->prev;
      }
      return *this;
    }

    LIter operator--(int)
    {
      LIter tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const LIter& other) const { return node_ == other.node_ && head_ == other.head_; }
    bool operator!=(const LIter& other) const { return !(*this == other); }

  private:
    LIter(Node< T >* node, Node< T >* head) : node_(node), head_(head) {}
    Node< T >* node_;
    Node< T >* head_;
  };

  template< class T >
  class LCIter
  {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    friend class BiList< T >;

    LCIter() : node_(nullptr), head_(nullptr) {}
    LCIter(const LIter< T >& other) : node_(other.node_), head_(other.head_) {}

    reference operator*() const { return node_->val; }
    pointer operator->() const { return &(node_->val); }

    LCIter& operator++()
    {
      if (node_)
      {
        node_ = node_->next;
        if (node_ == head_)
        {
          node_ = nullptr;
        }
      }
      return *this;
    }

    LCIter operator++(int)
    {
      LCIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LCIter& operator--()
    {
      if (!node_)
      {
        if (head_)
        {
          node_ = head_->prev;
        }
      }
      else if (node_ != head_)
      {
        node_ = node_->prev;
      }
      return *this;
    }

    LCIter operator--(int)
    {
      LCIter tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const LCIter& other) const { return node_ == other.node_ && head_ == other.head_; }
    bool operator!=(const LCIter& other) const { return !(*this == other); }

  private:
    LCIter(Node< T >* node, Node< T >* head) : node_(node), head_(head) {}
    Node< T >* node_;
    Node< T >* head_;
  };

  template< class T >
  class BiList
  {
  public:
    BiList() : head_(nullptr), size_(0) {}

    ~BiList() { clear(); }

    BiList(const BiList& other) : head_(nullptr), size_(0)
    {
      for (auto it = other.cbegin(); it != other.cend(); ++it)
      {
        pushBack(*it);
      }
    }

    BiList(BiList&& other) noexcept : head_(other.head_), size_(other.size_)
    {
      other.head_ = nullptr;
      other.size_ = 0;
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

    size_t getSize() const { return size_; }
    bool isEmpty() const { return size_ == 0; }

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

    LIter< T > begin() { return LIter< T >(head_, head_); }
    LIter< T > end() { return LIter< T >(nullptr, head_); }
    LCIter< T > cbegin() const { return LCIter< T >(head_, head_); }
    LCIter< T > cend() const { return LCIter< T >(nullptr, head_); }

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

    void pushBack(const T& value)
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
      }
      ++size_;
    }

    void popFront()
    {
      if (isEmpty()) return;
      if (size_ == 1)
      {
        delete head_;
        head_ = nullptr;
      }
      else
      {
        Node< T >* tail = head_->prev;
        Node< T >* oldHead = head_;
        head_ = head_->next;
        tail->next = head_;
        head_->prev = tail;
        delete oldHead;
      }
      --size_;
    }

    void clear()
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
