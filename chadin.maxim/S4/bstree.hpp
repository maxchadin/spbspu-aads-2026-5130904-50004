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

template <class Key, class Value>
class BSTConstIterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = const std::pair<const Key, Value>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;

  BSTConstIterator():
    node_(nullptr)
  {
  }

  explicit BSTConstIterator(NodeBase* node):
    node_(node)
  {
  }

  BSTConstIterator(const BSTIterator<Key, Value>& it):
    node_(it.node_)
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

  BSTConstIterator& operator++()
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

  BSTConstIterator operator++(int)
  {
    BSTConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  bool operator==(const BSTConstIterator& other) const
  {
    return node_ == other.node_;
  }

  bool operator!=(const BSTConstIterator& other) const
  {
    return node_ != other.node_;
  }

  NodeBase* node_;
};

template <class Key, class Value, class Compare = std::less<Key>>
class BSTree {
public:
  using iterator = BSTIterator<Key, Value>;
  using const_iterator = BSTConstIterator<Key, Value>;

  BSTree():
    size_(0)
  {
    fakeLeaf_.left = &fakeLeaf_;
    fakeLeaf_.right = &fakeLeaf_;
    fakeLeaf_.parent = &fakeLeaf_;

    fakeRoot_.parent = &fakeRoot_;
    fakeRoot_.left = &fakeLeaf_;
    fakeRoot_.right = &fakeLeaf_;
  }

  BSTree(const BSTree& other):
    BSTree()
  {
    for (auto it = other.cbegin(); it != other.cend(); ++it) {
      push(it->first, it->second);
    }
  }

  BSTree(BSTree&& other) noexcept :
    BSTree()
  {
    swap(other);
  }

  BSTree& operator=(const BSTree& other)
  {
    if (this != &other) {
      BSTree tmp(other);
      swap(tmp);
    }
    return *this;
  }

  BSTree& operator=(BSTree&& other) noexcept
  {
    swap(other);
    return *this;
  }

  ~BSTree()
  {
    clear();
  }

  void push(Key k, Value v)
  {
    NodeBase* curr = fakeRoot_.left;
    NodeBase* parent = &fakeRoot_;
    bool isLeft = true;

    while (!isFakeLeaf(curr)) {
      auto* n = static_cast<Node<Key, Value>*>(curr);
      if (comp_(k, n->data.first)) {
        parent = curr;
        curr = curr->left;
        isLeft = true;
      } else if (comp_(n->data.first, k)) {
        parent = curr;
        curr = curr->right;
        isLeft = false;
      } else {
        n->data.second = v;
        return;
      }
    }

    auto* newNode = new Node<Key, Value>(k, v);
    newNode->left = &fakeLeaf_;
    newNode->right = &fakeLeaf_;
    newNode->parent = parent;

    if (isFakeRoot(parent) || isLeft) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
    size_++;
  }

  Value get(Key k) const
  {
    NodeBase* node = findNode(k);
    if (isFakeLeaf(node)) {
      throw std::out_of_range("Key not found");
    }
    return static_cast<Node<Key, Value>*>(node)->data.second;
  }

  bool has(Key k) const
  {
    return !isFakeLeaf(findNode(k));
  }

  Value drop(Key k)
  {
    NodeBase* nodeT = findNode(k);
    if (isFakeLeaf(nodeT)) {
      throw std::out_of_range("Key not found");
    }

    Value droppedVal = static_cast<Node<Key, Value>*>(nodeT)->data.second;

    if (isFakeLeaf(nodeT->left) && isFakeLeaf(nodeT->right)) {
      replaceChild(nodeT, &fakeLeaf_);
    } else if (isFakeLeaf(nodeT->left)) {
      replaceChild(nodeT, nodeT->right);
    } else if (isFakeLeaf(nodeT->right)) {
      replaceChild(nodeT, nodeT->left);
    } else {
      NodeBase* minRight = nodeT->right;
      while (!isFakeLeaf(minRight->left)) {
        minRight = minRight->left;
      }

      replaceChild(minRight, minRight->right);

      minRight->parent = nodeT->parent;
      if (nodeT->parent->left == nodeT) {
        nodeT->parent->left = minRight;
      } else {
        nodeT->parent->right = minRight;
      }

      minRight->left = nodeT->left;
      if (!isFakeLeaf(minRight->left)) {
        minRight->left->parent = minRight;
      }

      minRight->right = nodeT->right;
      if (!isFakeLeaf(minRight->right)) {
        minRight->right->parent = minRight;
      }
    }

    delete static_cast<Node<Key, Value>*>(nodeT);
    size_--;
    return droppedVal;
  }
