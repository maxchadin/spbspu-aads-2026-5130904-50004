#ifndef CHADIN_NODE_HPP
#define CHADIN_NODE_HPP

#include <utility>

namespace chadin
{
  template< class T >
  struct Node
  {
    T val;
    Node* prev;
    Node* next;

    explicit Node(const T& value) : val(value), prev(nullptr), next(nullptr) {}
    explicit Node(T&& value) noexcept : val(std::move(value)), prev(nullptr), next(nullptr) {}
  };
}

#endif
