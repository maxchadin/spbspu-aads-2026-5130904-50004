#ifndef CHADIN_LCITER_HPP
#define CHADIN_LCITER_HPP

#include <iterator>
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
    friend class BiList< T >;

    LCIter() noexcept : node_(nullptr), head_(nullptr) {}
    LCIter(const LIter< T >& other) noexcept : node_(other.node_), head_(other.head_) {}

    typename LCIter::reference operator*() const
    {
      return node_->val;
    }

    typename LCIter::pointer operator->() const
    {
      return &(node_->val);
    }

    LCIter& operator++() noexcept
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
    LCIter(Node< T >* node, Node< T >* head) noexcept : node_(node), head_(head) {}
    Node< T >* node_;
    Node< T >* head_;
  };
}

#endif
