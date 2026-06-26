#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <stdexcept>
#include <iterator>
#include <algorithm>
#include "node.hpp"

namespace chadin {

template <class Key, class Value>
class BSTIterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = std::pair<const Key, Value>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  BSTIterator():
    node_(nullptr)
  {
  }

  explicit BSTIterator(NodeBase* node):
    node_(node)
  {
  }

  reference operator*() const
  {
    return static_cast<Node<Key, Value>*>(node_)->data;
  }

  pointer operator->() const
  {
    return &(static_cast<Node<Key, Value>*>(node_)->data);
  }

  BSTIterator& operator++()
  {
    if (node_->right->left != node_->right) {
      node_ = node_->right;
      while (node_->left->left != node_->left) {
        node_ = node_->left;
      }
    } else {
      NodeBase* p = node_->parent;
      while (p->parent != p && node_ == p->right) {
        node_ = p;
        p = p->parent;
      }
      node_ = p;
    }
    return *this;
  }

  BSTIterator operator++(int)
  {
    BSTIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  bool operator==(const BSTIterator& other) const
  {
    return node_ == other.node_;
  }

  bool operator!=(const BSTIterator& other) const
  {
    return node_ != other.node_;
  }

  NodeBase* node_;
};
