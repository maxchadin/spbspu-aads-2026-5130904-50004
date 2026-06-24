#ifndef CHADIN_BILIST_HPP
#define CHADIN_BILIST_HPP

#include <stdexcept>
#include <utility>
#include <cstddef>

namespace chadin
{
  template< class T >
  struct Node
  {
    T val;
    Node* prev;
    Node* next;

    Node(const T& value):
      val(value),
      prev(nullptr),
      next(nullptr)
    {}

    Node(T&& value):
      val(std::move(value)),
      prev(nullptr),
      next(nullptr)
    {}
  };

  template< class T >
  class BiList;

  template< class T >
  class LIter
  {
  public:
    friend class BiList< T >;

    LIter():
      node_(nullptr),
      head_(nullptr)
    {}

    T& operator*() const
    {
      return node_->val;
    }

    T* operator->() const
    {
      return &(node_->val);
    }

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
      if (node_ == nullptr)
      {
        if (head_)
        {
          node_ = head_->prev;
        }
      }
      else
      {
        if (node_ == head_)
        {
          node_ = nullptr;
        }
        else
        {
          node_ = node_->prev;
        }
      }
      return *this;
    }

    bool operator==(const LIter& other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const LIter& other) const
    {
      return !(*this == other);
    }

  private:
    Node< T >* node_;
    Node< T >* head_;

    LIter(Node< T >* node, Node< T >* head):
      node_(node),
      head_(head)
    {}
  };

  template< class T >
  class LCIter
  {
  public:
    friend class BiList< T >;

    LCIter():
      node_(nullptr),
      head_(nullptr)
    {}

    LCIter(const LIter< T >& other):
      node_(other.node_),
      head_(other.head_)
    {}

    const T& operator*() const
    {
      return node_->val;
    }

    const T* operator->() const
    {
      return &(node_->val);
    }

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

    LCIter& operator--()
    {
      if (node_ == nullptr)
      {
        if (head_)
        {
          node_ = head_->prev;
        }
      }
      else
      {
        if (node_ == head_)
        {
          node_ = nullptr;
        }
        else
        {
          node_ = node_->prev;
        }
      }
      return *this;
    }

    bool operator==(const LCIter& other) const
    {
      return node_ == other.node_;
    }

    bool operator!=(const LCIter& other) const
    {
      return !(*this == other);
    }

  private:
    const Node< T >* node_;
    const Node< T >* head_;

    LCIter(const Node< T >* node, const Node< T >* head):
      node_(node),
      head_(head)
    {}
  };

  template< class T >
  class BiList
  {
  public:
    BiList():
      head_(nullptr),
      size_(0)
    {}

    BiList(const BiList& other):
      head_(nullptr),
      size_(0)
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

    BiList(BiList&& other):
      head_(other.head_),
      size_(other.size_)
    {
      other.head_ = nullptr;
      other.size_ = 0;
    }

    ~BiList()
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

    void swap(BiList& other)
    {
      std::swap(head_, other.head_);
      std::swap(size_, other.size_);
    }

    bool isEmpty() const
    {
      return size_ == 0;
    }

    size_t getSize() const
    {
      return size_;
    }

    T& front()
    {
      return head_->val;
    }

    const T& front() const
    {
      return head_->val;
    }

    T& back()
    {
      return head_->prev->val;
    }

    const T& back() const
    {
      return head_->prev->val;
    }

    LIter< T > begin()
    {
      return LIter< T >(head_, head_);
    }

    LIter< T > end()
    {
      return LIter< T >(nullptr, head_);
    }

    LCIter< T > cbegin() const
    {
      return LCIter< T >(head_, head_);
    }

    LCIter< T > cend() const
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

    void pushBack(const T& value)
    {
      pushFront(value);
      head_ = head_->next;
    }

    void popFront()
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
