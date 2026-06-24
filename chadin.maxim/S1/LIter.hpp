#ifndef CHADIN_LITER_HPP
#define CHADIN_LITER_HPP

#include <iterator>
#include <cstddef>
#include "Node.hpp"

namespace chadin
{
  template< class T >
  class BiList;

  template< class T >
  class LCIter;

  template< class T >
  class LIter : public std::iterator< std::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T& >
  {
  public:
    friend class BiList< T >;
    friend class LCIter< T >;

    LIter() noexcept : node_(nullptr), head_(nullptr) {}

    typename LIter::reference operator*() const
    {
      return node_->val;
    }

    typename LIter::pointer operator->() const
    {
      return &(node_->val);
    }

    LIter& operator++() noexcept
    {
      if (node_ != nullptr)
      {
        node_ = node_->next;
        if (node_ == head_)
        {
          node_ = nullptr;
        }
      }
      return *this;
    }

    LIter operator++(int) noexcept
    {
      LIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LIter& operator--() noexcept
    {
      if (node_ == nullptr)
      {
        if (head_ != nullptr)
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

    LIter operator--(int) noexcept
    {
      LIter tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const LIter& other) const noexcept
    {
      return node_ == other.node_ && head_ == other.head_;
    }

    bool operator!=(const LIter& other) const noexcept
    {
      return !(*this == other);
    }

  private:
    Node< T >* node_;
    Node< T >* head_;
    LIter(Node< T >* node, Node< T >* head) noexcept : node_(node), head_(head) {}
  };
}

#endif
