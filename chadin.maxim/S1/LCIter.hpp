#ifndef CHADIN_LCITER_HPP
#define CHADIN_LCITER_HPP

#include <iterator>
#include <cstddef>
#include "Node.hpp"
#include "LIter.hpp"

namespace chadin
{
  template< class T >
  class BiList;

  template< class T >
  class LCIter : public std::iterator< std::bidirectional_iterator_tag, const T >
  {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const T*;
    using reference         = const T&;

    friend class BiList< T >;

    LCIter() noexcept :
      node_(nullptr),
      head_(nullptr)
    {}

    LCIter(const Node< T >* node, const Node< T >* head) noexcept :
      node_(const_cast< Node< T >* >(node)),
      head_(const_cast< Node< T >* >(head))
    {}

    LCIter(const LIter< T >& other) noexcept :
      node_(other.node_),
      head_(other.head_)
    {}

    reference operator*() const noexcept
    {
      return node_->val;
    }

    pointer operator->() const noexcept
    {
      return &(node_->val);
    }

    LCIter& operator++() noexcept
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

    LCIter operator++(int) noexcept
    {
      LCIter tmp(*this);
      ++(*this);
      return tmp;
    }

    LCIter& operator--() noexcept
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

    LCIter operator--(int) noexcept
    {
      LCIter tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const LCIter& other) const noexcept
    {
      return node_ == other.node_ && head_ == other.head_;
    }

    bool operator!=(const LCIter& other) const noexcept
    {
      return !(*this == other);
    }

  private:
    Node< T >* node_;
    Node< T >* head_;
  };
}

#endif
