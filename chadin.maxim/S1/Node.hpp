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

    Node(const T& value) : val(value), prev(nullptr), next(nullptr) {}
    Node(T&& value) : val(std::move(value)), prev(nullptr), next(nullptr) {}
  };
}

#endif
