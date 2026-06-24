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
  class LIter : public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;

    friend class BiList< T >;

    LIter() noexcept :
      node_(nullptr),
      head_(nullptr)
    {}

    LIter(Node< T >* node, Node< T >* head) noexcept :
      node_(node),
      head_(head)
    {}

    reference operator*() const noexcept
    {
      return node_->val;
    }

    pointer operator->() const noexcept
    {
      return &(node_->val);
    }

    LIter& operator++() noexcept
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
        if (head_)
        {
          node_ = head_->prev;
        }
      }
      else
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
  };
}

#endif
